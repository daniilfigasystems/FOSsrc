#ifndef _KPRINTF_
#define _KPRINTF_

struct memcell
{
	unsigned char ch;
	unsigned char color;
};

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