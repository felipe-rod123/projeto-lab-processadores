#ifndef SYSCALL_H
#define SYSCALL_H

#include <sys/stat.h>

int _fstat(int file, struct stat *st);
int _lseek(int file, int offset, int whence);
int _close(int fd);
int _write(int fd, char *buf, int count);
int _read(int fd, char *buf, int count);
void *_sbrk(int incr);
int _isatty(int file);
void _exit(int status);
void _kill(int pid, int sig);
int _getpid(void);

#endif // SYSCALL_H
