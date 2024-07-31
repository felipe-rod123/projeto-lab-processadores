#include <sys/stat.h>
#include <stdint.h>
#include "uart.h"
#include "syscall.h"


extern uint32_t inicio_heap;

int _fstat(int file, struct stat *st) {
  st->st_mode = S_IFCHR;
  return 0;
}

int _lseek(int file, int offset, int whence) {
  return 0;
}

int _close(int fd) {
  return -1;
}

int _write (int fd, char *buf, int count) {
   if(fd == 1) {
      while(count--) {
         mini_uart_putc(*buf++);
      }
   }
   return count;
}

int _read (int fd, char *buf, int count) {
   if(fd == 0) {
      while(count--) {
         *buf++ = mini_uart_getc();
      }
   }
   return 0;
}

void *_sbrk(int incr) {
  static uint8_t *brk = (uint8_t*)&inicio_heap;
  uint8_t *prev;
  prev = brk;
  brk += incr;
  return prev;
}

int _isatty(int file) {
  return 1;
}

void _exit(int status) {
   for(;;);
}

void _kill(int pid, int sig) {
   return;
}

int _getpid(void) {
   return 1;
}
