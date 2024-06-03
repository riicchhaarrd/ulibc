#include "string.h"

void* memset(void *p_, int value, size_t n)
{
	char *p = (char *)p_;
	for(int i = 0; i < n; ++i)
	{
		p[i] = value & 0xff;
	}
	return p_;
}

void *memcpy(void *dst, const void *src, size_t n)
{
	char *dst_ = (char *)dst;
	char *src_ = (char *)src;
	for(int i = 0; i < n; ++i)
	{
		dst_[i] = src_[i];
	}
	return dst;
}
