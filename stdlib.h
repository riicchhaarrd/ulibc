#ifndef STDLIB_H
#define STDLIB_H

#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <stddef.h>

#ifdef USE_AMD64_INLINE_ASM
asm("exit:\n\
			 mov $0x3c,%rax\n\
			 syscall\n\
			 ret\n\
			 ");
#endif

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

#ifdef USE_AMD64_INLINE_ASM
__attribute__((__cdecl__)) int brk(void *addr);
asm("brk:\n\
			 mov $0xc,%rax\n\
			 syscall\n\
			 ret\n\
			 ");
#else
__attribute__((__cdecl__)) void* sbrk(intptr_t);
#endif

void *malloc(int size)
{
#ifdef USE_AMD64_INLINE_ASM
	int current = brk(0);
	int next = brk((void *)(current + size));
	// printf("current=%x,next=%x\n",current,next);
	return current == next ? (void *)NULL : (void *)current;
#else
	return sbrk(size);
#endif
}

void free(void *p)
{
    //does nothing atm
}
#endif
