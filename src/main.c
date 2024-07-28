#include "uart.h"
#include "i2c.h"
#include <stdio.h>

void main(void) {
   mini_uart_init(115200);
   int val;
   i2c_init();
      while (true)
      {
         val = smbus_read_byte(SENSOR_ADRESS, IDENTIFICATION_MODEL_ID);
         printf("tentando identificar sensor...\n");
         if (val == 0xEE) 
       { 
       printf("sensor identificado!\n");
       printf("val:%x", val);
       printf("\n");
       printf("\n");
       printf("\n");
       printf("\n");
       printf("\n");
       }
       else{
       printf("ERRO\n");
       }
       delay(15000);
      }
}
