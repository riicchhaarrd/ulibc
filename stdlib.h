#ifndef STDLIB_H
#define STDLIB_H

#include <sys/syscall.h>
#include <unistd.h>
#include <stddef.h>

asm("exit:\n\
			 mov $0x3c,%rax\n\
			 syscall\n\
			 ret\n\
			 ");


__attribute__((__cdecl__,noreturn)) void exit(int status);

int main(int argc, char **argv);
void _start()
{
	int status = main(0, NULL);
	/* __builtin_trap(); */
	exit(status);
}

/* void exit(int code) */
/* { */
/*     syscall(SYS_exit, code); */
/* } */

int atoi(const char *_str)
{
    int total = 0;
    int len = 0;
    const char *str = _str;
    int neg = *str == '-';
    if(neg)
        ++str;
    const char *p = str;
    while(*p++) ++len;
    int exp = 1;
    for(int i = 0; i < len; ++i)
	{
        int t = str[len - i - 1] - '0';
        total += t * exp;
        exp *= 10;
	}
    if(neg)
        return -total;
	return total;
}

void *malloc(int size)
{
    int current = brk(0);
    int next = brk(current + size);
    //printf("current=%x,next=%x\n",current,next);
    return current == next ? NULL : current;
}

void free(void *p)
{
    //does nothing atm
}
#endif
