
#include <stdint.h>
#include "bcm.h"

char msg[] = "Hello\r\n";

void delay(uint32_t dur);

/**
 * Configura a mini-uart para 115200
 */
void uart_init(void) {
   /*
    * Configura os GPIO 14 e 15 com a função alternativa 2 (UART).
    */
   uint32_t sel = GPIO_REG(gpfsel[1]);
   sel = (sel & (~(7<<12))) | (2<<12);
   sel = (sel & (~(7<<15))) | (2<<15);
   GPIO_REG(gpfsel[1]) = sel;

   /*
    * Configura pullups nos pinos
    */
   GPIO_REG(gppud) = 0;
   delay(150);
   GPIO_REG(gppudclk[0]) = (1 << 14) | (1 << 15);
   delay(150);
   GPIO_REG(gppudclk[0]) = 0;

   /*
    * Configura o periférico da mini uart
    */
   AUX_REG(enables) = 1;
   MU_REG(cntl) = 0;
   MU_REG(ier) = 0;
   MU_REG(lcr) = 3;           // 8 bits
   MU_REG(mcr) = 0;
   MU_REG(baud) = 270;        // para 115200 bps em 250 MHz
   MU_REG(cntl) = 3;          // habilita TX e RX
}

/**
 * Envia um caractere pela uart.
 */
void uart_putc(uint8_t c) {
   while((MU_REG(lsr) & 0x20) == 0) ;
   MU_REG(io) = c;
}

/**
 * Envia um string (terminado em zero) pela uart.
 * Suspende o processamento até terminar.
 */
void uart_puts(char *s) {
   while(*s) {
      uart_putc(*s);
      s++;
   }
}

/**
 * Lê um caractere pela uart.
 * Suspende o processamento até receber.
 */
uint8_t uart_getc(void) {
   while((MU_REG(lsr) & 0x01) == 0) ;
   return MU_REG(io);
}




   
void printa_oi(int q) {
   return ;
   uint8_t c = 'o';
   int i = 0;
   for (i =0;i <q; i++)
   {
      uart_putc(c);
   }
   c = '\n';
   uart_putc(c);
   return ;
}


int periodo_alto_pwm_em_micro_segundos_dado_angulo(int angulo_em_graus)
{
   // ang max em graus = 90; 
   // ang min em graus = -90;
   // periodo max em micro s  = 2000;
   // periodo min em micro s  = 1000;
   // periodo'(ang) é constante
   // => (angulo_em_graus*500)/90 + 1500
   return (angulo_em_graus*500)/90 + 1500;
}

int distancia_em_mm_dada_duracao_echo(int duracao_echo_em_micro_segundos)
{
   // duracao echo em s = duracao echo em micro s/1000000
   // velocidade do som em m/s = 343
   // distancia em mm = 1000 * distancia  em m 
   // 2 * distancia em m = ( velocidade do som em m/s ) * echo em s

   // => distancia em mm  = (343 * echo/1000000)*1000/2 =
   if (( (duracao_echo_em_micro_segundos*343)/2000) < 160 )
   { 
      return (duracao_echo_em_micro_segundos*343)/2000;
   }
   else
   {
      return -1;
   }
}






int printa_1_o_por_ms(int q) 
{
   uint8_t c = '.';
   int i = 0;
   int distancia_em_mm =  distancia_em_mm_dada_duracao_echo(q);
   for (i =0;i <=distancia_em_mm; i+=1) // 1000
   {
      uart_putc(c);
   }
   c = '\n';
   uart_putc(c);
   if (distancia_em_mm == -1)
   {
      c = 'o';
      uart_putc(c);
      return  periodo_alto_pwm_em_micro_segundos_dado_angulo(9000);
   }

   return  periodo_alto_pwm_em_micro_segundos_dado_angulo(0);
}
