#ifndef _STDARG_
#define _STDARG_

#define va_start(v,l) __builtin_va_start(v,l)
#define va_end(v) __builtin_va_end(v)
#define va_arg(v,l) __builtin_va_arg(v,l)
#if !defined(__STRICT_ANSI__) || __STDC_VERSION__ + 0 >= 199900L
#define va_copy(d,s)  __builtin_va_copy(d,s)
#endif
#define __va_copy(d,s)  __builtin_va_copy(d,s)

#endif /* !_STDARG_! */