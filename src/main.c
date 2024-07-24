#include "uart.h"
#include <stdio.h>

void main(void) {

    mini_uart_init(115200);
    
    while (1){
		printf("Hello World!\n");      
	}
}