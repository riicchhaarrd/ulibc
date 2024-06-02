#ifndef STDDEF_H
#define STDDEF_H

#ifndef NULL
	#define NULL ((void *)0)
#endif

#include <stdint.h>

#if INTPTR_MAX == INT64_MAX

typedef long long ssize_t;
typedef unsigned long long size_t;

#elif INTPTR_MAX == INT32_MAX

typedef int ssize_t;
typedef unsigned int size_t;

#else
#error Unknown pointer size
#endif

typedef uint32_t wchar_t;

#endif
