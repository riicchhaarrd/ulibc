#ifndef STDLIB_H
#define STDLIB_H

#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>

#ifdef USE_AMD64_INLINE_ASM
asm("exit:\n\
			 mov $0x3c,%rax\n\
			 syscall\n\
			 ret\n\
			 ");
#endif

__attribute__((__cdecl__,noreturn)) void exit(int status);

/* int main(int argc, char **argv); */
/* void _start() */
/* { */
/* 	int status = main(0, NULL); */
/* 	/\* __builtin_trap(); *\/ */
/* 	exit(status); */
/* } */

/* void exit(int code) */
/* { */
/*     syscall(SYS_exit, code); */
/* } */

static int atoi(const char *_str)
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

// TODO: FIXME
// Scan for integral and fractional and then just combine them

static double atof(const char *str)
{
	return (double)atoi(str);
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

static void *malloc(int size)
{
	size += sizeof(size_t);

	void *p = NULL;
	
#ifdef USE_AMD64_INLINE_ASM
	int current = brk(0);
	int next = brk((void *)(current + size));
	if(current != next)
	{
		p = current;
	}
#else
	p = sbrk(size);
#endif
	
	*(size_t*)p = size;
	p = (char*)p + sizeof(size_t);
	return p;
}

static void *calloc(size_t nitems, size_t size)
{
	void *p = malloc(nitems * size);
	memset(p, 0, nitems * size);
	return p;
}

static void free(void *p)
{
    //does nothing atm
}

static void *realloc(void *ptr, size_t new_size)
{
	void *p = malloc(new_size);
	if(NULL == ptr)
	{
		return p;
	}
	size_t current_size = *(size_t*)((char*)ptr - sizeof(size_t));
	size_t least = new_size < current_size ? new_size : current_size;
	memcpy(p, ptr, least);
	free(ptr);
	return p;
}

static int abs(int n)
{
	return n < 0 ? -n : n;
}

static long labs(long n)
{
	return n < 0 ? -n : n;
}

//TODO: FIXME
static long int strtol(const char *str, char **endptr, int base)
{
	return 0;
}
#endif
