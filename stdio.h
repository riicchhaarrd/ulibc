#ifndef STDIO_H
#define STDIO_H

#include <sys/syscall.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

#define STDOUT_FILENO 1
#define STDIN_FILENO 0
#define STDERR_FILENO 2

typedef struct
{
	int unused;
} FILE;

static void print(const char *s)
{
    write(STDOUT_FILENO, s, strlen(s) + 1);
}

static int getchar()
{
    char buf[1];
    read(STDIN_FILENO, buf, 1);
    return buf[0];
}

static void putchar(int ch)
{
    char buf[2];
    buf[0] = ch;
    buf[1] = 0;
    print(buf);
}

static void print_hex(int d)
{
    for(int i = 0; i < 8; ++i)
	{
		int nibble = ( d >> ( ( 8 - i - 1 ) * 4 ) ) & 15;
		putchar( nibble >= 10 ? 'A' + nibble - 10 : '0' + nibble );
	}
}

static void print_decimal(int d)
{
    int neg = d < 0;
    if(neg)
        d = -d;
    char buf[32];
    int i = 0;
    buf[31] = 0;
    do
	{
        int m = d % 10;
        buf[sizeof(buf) - i - 2] = m + '0';
        d /= 10;
        i += 1;
	} while(d > 0);
    if(neg)
	{
		buf[sizeof( buf ) - i - 2] = '-';
		++i;
	}
	print(&buf[sizeof(buf) - i - 1]);
}

static void print_float(float f)
{
	int integral;
	float fractional = modf(f, &integral);
	print_decimal(integral);
	putchar('.');
	print_decimal(fractional * 100.f);
}

static void print_bits(int d, int little_endian)
{
    char buf[33];
    for(int i = 0; i < 32; ++i)
	{
		int b = d & ( 1 << i );
		buf[little_endian ? 32-i-1 : i] = b ? '1' : '0';
	}
	buf[32] = 0;
    print(buf);
	//write( STDOUT_FILENO, buf, sizeof(buf) );
}

static int printf(const char *fmt, ...)
{
    va_list q;
    va_start(q, fmt);
    int l = strlen(fmt);
    for(int i = 0; i < l; ++i)
	{
		if(fmt[i] == '%')
		{
			int ch = fmt[i + 1];
			switch(ch)
			{
				case 'd':
				{
					int argd = va_arg(q, int);
					print_decimal(argd);
				}
				break;
				case 's':
				{
					const char *args = va_arg(q, const char *);
					print(args);
				}
				break;
				case 'x':
				{
					int argx = va_arg(q, int);
					print_hex(argx);
				}
				break;
				case 'b':
				{
					int argb = va_arg(q, int);
					print_bits(argb, 1);
				}
				break;
				case 'B':
				{
					int argb = va_arg(q, int);
					print_bits(argb, 0);
				}
				break;
				case 'f':
				{
					float argf = (float)va_arg(q, double);
					print_float(argf);
				}
				break;
			}
			++i;
		}
		else
			putchar( fmt[i] );
	}
	va_end(q);
    return 0;
}

static int snprintf(char *s, size_t n, const char *format, ...)
{
	return -1;
}
static int vsnprintf(char *s, size_t n, const char *format, va_list arg)
{
	return -1;
}

static size_t fread(void *buffer, size_t size, size_t count, FILE *stream)
{
	return 0;
}

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

static int fseek(FILE *stream, long offset, int origin)
{
	return -1;
}

static int ferror(FILE *stream)
{
	return -1;
}

#define EOF (-1)

static int fgetc(FILE *stream)
{
	return EOF;
}

static int ungetc(int ch, FILE *stream)
{
	return EOF;
}

static int feof(FILE *stream)
{
	return EOF;
}

static FILE *fopen(const char *filename, const char *mode)
{
	return NULL;
}

static int fclose(FILE *stream)
{
	return EOF;
}

static long ftell(FILE *stream)
{
	return -1L;
}
#endif
