#ifndef STDINT_H
#define STDINT_H

#define INT16_MAX (0xffff)
#define INT32_MAX (0xffffffff)
#define INT64_MAX (0xffffffffffffffff)

#if __x86_64__
#define INTPTR_MAX INT64_MAX
#else
#define INTPTR_MAX INT32_MAX
#endif

typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;

#if INTPTR_MAX == INT64_MAX
typedef long long intptr_t;
typedef unsigned long long uintptr_t;
#elif INTPTR_MAX == INT32_MAX
typedef int intptr_t;
typedef unsigned int uintptr_t;
#else
#error Unknown pointer size
#endif

#endif
