
#include <stdint.h>
#include "bcm.h"

char msg[] = "Hello\r\n";
int vetor_medida_3[12] = {10,10,10,10,10,10,10,10,10,10,10,10};
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

 void init(void)
 {
   vetor_medida_3[0] = 90;
   vetor_medida_3[1] = 90;
   vetor_medida_3[2] = 90;
   vetor_medida_3[3] = 90;
   vetor_medida_3[4] = 90;
   vetor_medida_3[5] = 90;
   vetor_medida_3[6] = 90;
   vetor_medida_3[7] = 90;
   vetor_medida_3[8] = 90;
   vetor_medida_3[9] = 90;
   vetor_medida_3[10] = 90;
   vetor_medida_3[11] = 90;

   uart_init();
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




   


int periodo_alto_pwm_em_micro_segundos_dado_angulo(int angulo_em_graus)
{
   // ang max em graus = 90; 
   // ang min em graus = -90;
   // periodo max em micro s  = 2000;
   // periodo min em micro s  = 1000;
   // periodo'(ang) é constante
   // => (angulo_em_graus*500)/90 + 1500
   if  (angulo_em_graus > 90)
   {
      return (90*500)/90 + 1500;
   }
   if  (angulo_em_graus < -90)
   {
      return (-90*500)/90 + 1500;
   }

   return (angulo_em_graus*500)/90 + 1500;
}

int distancia_em_mm_dada_duracao_echo(int duracao_echo_em_micro_segundos)
{
   // duracao echo em s = duracao echo em micro s/1000000
   // velocidade do som em m/s = 343
   // distancia em mm = 1000 * distancia  em m 
   // 2 * distancia em m = ( velocidade do som em m/s ) * echo em s

   // => distancia em mm  = (343 * echo/1000000)*1000/2 =
   if (( (duracao_echo_em_micro_segundos*343)/2000) < 180 )
   { 
      return (duracao_echo_em_micro_segundos*343)/2000;
   }
   else
   {
      return -1;
   }
}



int controle(int largura_echo_em_micro_segundos) 
{

   uint8_t c = '.';

   int i = 0;
   int distancia_em_mm =  distancia_em_mm_dada_duracao_echo(largura_echo_em_micro_segundos);
   for (i =0;i <=distancia_em_mm; i+=1) // 1000
   {
      uart_putc(c);
   }
   c = '\n';
   uart_putc(c);
      
   /*c = 'a';
   for (i =0;i <=angulo; i+=1) // 1000
   {
      uart_putc(c);
   }
   c = 'l';
   uart_putc(c);
   */
   c = '\n';
   uart_putc(c);


   if (distancia_em_mm == -1)
   {
      c = 'o';
      uart_putc(c);
      return  periodo_alto_pwm_em_micro_segundos_dado_angulo(9900);
   }
   
   

   vetor_medida_3[11] = vetor_medida_3[10];
   vetor_medida_3[10] = vetor_medida_3[9];
   vetor_medida_3[9] = vetor_medida_3[8];
   vetor_medida_3[8] = vetor_medida_3[7];
   vetor_medida_3[7] = vetor_medida_3[6];
   vetor_medida_3[6] = vetor_medida_3[5];

   vetor_medida_3[5] = vetor_medida_3[4];
   vetor_medida_3[4] = vetor_medida_3[3];
   vetor_medida_3[3] = vetor_medida_3[2];
   vetor_medida_3[2] = vetor_medida_3[1];
   vetor_medida_3[1] = vetor_medida_3[0];
   vetor_medida_3[0] = distancia_em_mm;

   int medida ;
   int d_zero = 94;
   int k = 8/100;
   int ang;
   int tipo_controle = 0;
   if (tipo_controle==0){
      k = 8/100;
      medida = distancia_em_mm;
   }   
   if (tipo_controle==1){
      k = 8/100;
      medida = (vetor_medida_3[0] + vetor_medida_3[1] + vetor_medida_3[2] + vetor_medida_3[3] + vetor_medida_3[4] + vetor_medida_3[5])/6 ;
      ang = (medida-d_zero)*k;
   }   
   if (tipo_controle==2){
      k = 60/100;
      medida = (vetor_medida_3[0] + vetor_medida_3[1] + vetor_medida_3[2] + vetor_medida_3[3] + vetor_medida_3[4] + vetor_medida_3[5])/6 
             - (vetor_medida_3[6] + vetor_medida_3[7] + vetor_medida_3[8] + vetor_medida_3[9] + vetor_medida_3[10] + vetor_medida_3[11])/6;
      ang = (medida)*k;
   }   



   c = ',';
   int j = 0;
   for (j =0;j <medida; j++)
   {
      uart_putc(c);
   }
   c = '\n';
   uart_putc(c);




   if (ang > 5)
   {
      c = '_';
      uart_putc(c);
      c = '_';
      uart_putc(c);
      c = '_';
      uart_putc(c);
      c = '_';
      uart_putc(c);
      c = 'O';
      uart_putc(c);
      c = '\n';

      uart_putc(c);
      c = ' ';
      uart_putc(c);
      c = ' ';
      uart_putc(c);
      c = 'V';
      uart_putc(c);
      c = ' ';
      uart_putc(c);
      c = ' ';
      uart_putc(c);
      c = '\n';
      uart_putc(c);
   }
   if (ang < -5)
   {
      c = 'O';
      uart_putc(c);
      c = ' ';
      uart_putc(c);
      c = '_';
      uart_putc(c);
      c = '_';
      uart_putc(c);
      c = '_';
      uart_putc(c);
      c = '\n';

      uart_putc(c);
      c = ' ';
      uart_putc(c);
      c = ' ';
      uart_putc(c);
      c = 'V';
      uart_putc(c);
      c = ' ';
      uart_putc(c);
      c = ' ';
      uart_putc(c);
      c = '\n';
      uart_putc(c);
   }
   if ((ang >= -5) && (ang <= 5))
   {
      c = '_';
      uart_putc(c);
      c = '_';
      uart_putc(c);
      c = 'V';
      uart_putc(c);
      c = '_';
      uart_putc(c);
      c = '_';
      uart_putc(c);
      c = '\n';

      uart_putc(c);
      c = ' ';
      uart_putc(c);
      c = ' ';
      uart_putc(c);
      c = 'V';
      uart_putc(c);
      c = ' ';
      uart_putc(c);
      c = ' ';
      uart_putc(c);
      c = '\n';
      uart_putc(c);
   }




   if (ang > 90)
   {
      c = '+';
      uart_putc(c);
      return  periodo_alto_pwm_em_micro_segundos_dado_angulo(9900);
   }
   if (ang < -90)
   {
      c = '-';
      uart_putc(c);
      return  periodo_alto_pwm_em_micro_segundos_dado_angulo(9900);
   }




   return periodo_alto_pwm_em_micro_segundos_dado_angulo(ang);
}
