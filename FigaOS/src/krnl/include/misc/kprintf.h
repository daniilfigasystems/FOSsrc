#ifndef _KPRINTF_
#define _KPRINTF_

int
vasprintf(
    char * buf, const char *fmt, __builtin_va_list args
);
int
kprintf(
	const char *fmt,
	...
);

#endif /* !_KPRINTF_! */