#ifndef STDARG_H
#define STDARG_H

/* #define va_list void** */
/* #define va_start(va, fmt) va = &fmt + sizeof(fmt) */
/* #define va_arg(va, type) *va, va += sizeof(type) */
/* #define va_end(va) va = 0 */

#define va_list __builtin_va_list
#define va_start __builtin_va_start
#define va_arg __builtin_va_arg
#define va_end __builtin_va_end
#endif
