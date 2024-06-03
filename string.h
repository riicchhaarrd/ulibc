#ifndef STRING_H
#define STRING_H
#include <stddef.h>

static int strlen(const char *s)
{
    int len = 0;
    while(*s++) len++;
    return len;
}

static int strcmp(const char *a, const char *b)
{
    int al = strlen(a);
    int bl = strlen(b);
    if(al != bl)
        return 1;
    for(int i = 0; i < al; ++i)
	{
        if(a[i] != b[i])
            return 1;
	}
    return 0;
}

static void memset(void *p_, int value, size_t n)
{
	char *p = (char *)p_;
	for(int i = 0; i < n; ++i)
	{
		p[i] = value & 0xff;
	}
}

static void *memcpy(void *dst, const void *src, size_t n)
{
	char *dst_ = (char *)dst;
	char *src_ = (char *)src;
	for(int i = 0; i < n; ++i)
	{
		dst_[i] = src_[i];
	}
	return dst;
}

static void *memmove(void *destination, const void *source, size_t n)
{
	unsigned char *dst = destination;
	const unsigned char *src = source;

	if(dst == src)
		return dst;

	if(dst < src)
	{
		for(size_t i = 0; i < n; ++i)
		{
			dst[n - i - 1] = src[n - i - 1];
		}
		return dst;
	}
	memcpy(dst, src, n);
	return dst;
}

static char *strncat(char *destination, const char *source, size_t num)
{
	size_t i;
	size_t len = strlen(destination);
	for(i = 0; i < num; ++i)
	{
		destination[len + i] = source[i];
	}
	destination[i] = 0;
	return destination;
}
#endif
