#ifndef UNISTD_H
#define UNISTD_H

/* int read(int fd, char *buf, int len) */
/* { */
/*     return syscall(SYS_read, fd, buf, len); */
/* } */

/* void write(int fd, const char *buf, int len) */
/* { */
/*     syscall(SYS_write, fd, buf, len); */
/* } */


// https://www.ired.team/miscellaneous-reversing-forensics/windows-kernel-internals/linux-x64-calling-convention-stack-frame
// Arguments 1-6 are accessed via registers RDI, RSI, RDX, RCX, R8, R9
// https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/
asm("write:\n\
			 mov $0x1,%rax\n\
			 mov $0x1,%rdi\n\
			 syscall\n\
			 ret\n\
			 ");

// fd = RDI
// buf = RSI
// count = RDX
__attribute__((__cdecl__)) ssize_t write(int fd, const void *buf, size_t count);

asm("read:\n\
			 mov $0x0,%rax\n\
			 mov $0x0,%rdi\n\
			 syscall\n\
			 ret\n\
			 ");
__attribute__((__cdecl__)) ssize_t read(int fd, void *buf, size_t count);

/* int sleep(int sec) */
/* { */
/*     int d[2]; */
/*     d[0] = sec; */
/*     d[1] = 0; */

/*     int ret = syscall(SYS_nanosleep, d, 0); */
/*     //TODO: handle EINTR */
/*     if(ret < 0) */
/* 	{ */
/*         int errno = -ret; */
/* 		//printf( "sleep failed, ret = %x %d\n", errno, errno); */
/*         return sec; */
/* 	} */
/*     return 0; */
/* } */

__attribute__((__cdecl__)) int brk(void *addr);
asm("brk:\n\
			 mov $0xc,%rax\n\
			 syscall\n\
			 ret\n\
			 ");
#endif
