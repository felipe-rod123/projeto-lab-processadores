#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "bcm.h"

/**
 * Inicia canal 1 do I2C (GPIO 2 e 3)
 */
void i2c_init(void) {
   // GPIOs 2 e 3, função alternativa ALT0
   uint32_t sel = GPIO_REG(gpfsel[0]);
   sel = (sel & (~(0x3f<<6))) | (4 << 6) | (4 << 9);
   GPIO_REG(gpfsel[0]) = sel;          // GPIO 2 e 3

   set_bit(BSC_REG(1, c), 15);         // habilita I2C
}

/**
 * Envia um buffer através do canal I2C.
 * @param addr Endereço do slave (0-127)
 * @param ptr Ponteiro para os dados.
 * @param size Quantidade de bytes a enviar.
 * @return true se bem sucedido (o slave enviou ACK).
 */
bool 
i2c_write(uint8_t addr, uint8_t *ptr, unsigned size) {
   // reinicia CLKT, ERR e DONE
   BSC_REG(1, s) |= ((1 << 9) | (1 << 8) | (1 << 1));
   set_bit(BSC_REG(1, c), 4);                      // limpa FIFO
   BSC_REG(1, a) = addr;                           // configura endereço
   clr_bit(BSC_REG(1, c), 0);                      // escrita
   BSC_REG(1, dlen) = size;                        // número de bytes a transferir
   set_bit(BSC_REG(1, c), 7);                      // gera start condition

   while(bit_not_set(BSC_REG(1, s), 1)) {          // done
      if(bit_is_set(BSC_REG(1, s), 4)) {           // TXD 
         BSC_REG(1, fifo) = *ptr;                  // envia o próximo
         ptr++;
      } else if(bit_is_set(BSC_REG(1, s), 8)) {    // ERR
         return false;
      }
   }
   return true;
}

/**
 * Recebe um buffer através do canal I2C.
 * @param addr Endereço do slave (0-127)
 * @param ptr Ponteiro para salvar os dados.
 * @param size Quantidade de bytes a receber.
 * @return true se bem sucedido (o slave enviou ACK).
 */
bool 
i2c_read(uint8_t addr, uint8_t *ptr, unsigned size) {
   // reinicia CLKT, ERR e DONE
   BSC_REG(1, s) |= ((1 << 9) | (1 << 8) | (1 << 1));
   set_bit(BSC_REG(1, c), 4);                      // limpa FIFO
   BSC_REG(1, a) = addr;                           // configura endereço
   set_bit(BSC_REG(1, c), 0);                      // leitura
   BSC_REG(1, dlen) = size;                        // número de bytes a transferir
   set_bit(BSC_REG(1, c), 7);                      // gera start condition

   while(bit_not_set(BSC_REG(1, s), 1)) {          // done
      if(bit_is_set(BSC_REG(1, s), 5)) {           // RXD 
         *ptr = BSC_REG(1, fifo);                  // lê um byte
         ptr++;
      } else if(bit_is_set(BSC_REG(1, s), 8)) {    // ERR
         return false;
      }
   }
   return true;
}

/**
 * Funções para o protocolo SMB (escrita em registradores sobre I2C)
 * @param addr Endereço do slave (0-127).
 * @param reg Endereço do registrador interno ao slave.
 * @param val Valor a escrever (byte).
 * @return true se bem sucedido.
 */
bool 
smbus_write_byte(uint8_t addr, uint8_t reg, uint8_t val) {
   uint8_t buf[2] = { reg, val };
   return i2c_write(addr, buf, 2);
}

/**
 * Funções para o protocolo SMB (escrita em registradores sobre I2C)
 * @param addr Endereço do slave (0-127).
 * @param reg Endereço do registrador interno ao slave.
 * @param val Valor a escrever (16 bits).
 * @return true se bem sucedido.
 */
bool 
smbus_write_word(uint8_t addr, uint8_t reg, uint16_t val) {
   uint8_t buf[3] = { reg, val >> 8, val & 0xff };
   return i2c_write(addr, buf, 3);
}

/**
 * Funções para o protocolo SMB (escrita em registradores sobre I2C)
 * @param addr Endereço do slave (0-127).
 * @param reg Endereço do registrador interno ao slave.
 * @return Valor lido (byte sem sinal) ou -1 em caso de erro.
 */
int 
smbus_read_byte(uint8_t addr, uint8_t reg) {
   uint8_t buf[1] = { reg };
   if(!i2c_write(addr, buf, 1)) return -1; //escreve no bus o endereço do reg que a gnt quiser ler
   if(!i2c_read(addr, buf, 1)) return -1; //lê no bus os dados colocados pelo slave
   return buf[0];
}

/**
 * Funções para o protocolo SMB (escrita em registradores sobre I2C)
 * @param addr Endereço do slave (0-127).
 * @param reg Endereço do registrador interno ao slave.
 * @return Valor lido (16 bits sem sinal) ou -1 em caso de erro.
 */
int smbus_read_word(uint8_t addr, uint8_t reg) {
   uint8_t buf[2] = { reg, 0 };
   if(!i2c_write(addr, buf, 1)) return -1;
   if(!i2c_read(addr, buf, 2)) return -1;
   return (buf[0] << 8) | buf[1];
}