#ifndef __UART_H__
#define __UART_H__

void mini_uart_init(unsigned baud);
void mini_uart_putc(char c);
char mini_uart_getc(void);
void delay(int c);

#endif