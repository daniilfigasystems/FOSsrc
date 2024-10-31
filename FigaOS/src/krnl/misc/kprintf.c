#include "misc/kprintf.h"
#include "libs/headers/stdarg.h"
#include "libs/headers/string.h"
#include "vga/vga.h"
#include "io/io.h"

static void print_dec(unsigned int value, unsigned int width, char * buf, int * ptr ) {
	unsigned int n_width = 1;
	unsigned int i = 9;
	while (value > i && i < 4294967295) {
		n_width += 1;
		i *= 10;
		i += 9;
	}

	int printed = 0;
	while (n_width + printed < width) {
		buf[*ptr] = '0';
		*ptr += 1;
		printed += 1;
	}

	i = n_width;
	while (i > 0) {
		unsigned int n = value / 10;
		int r = value % 10;
		buf[*ptr + i - 1] = r + '0';
		i--;
		value = n;
	}
	*ptr += n_width;
}

static void print_hex(unsigned int value, unsigned int width, char * buf, int * ptr) {
	int i = width;

	if (i == 0) i = 8;

	unsigned int n_width = 1;
	unsigned int j = 0x0F;
	while (value > j && j < 4294967295) {
		n_width += 1;
		j *= 0x10;
		j += 0x0F;
	}

	while (i > (int)n_width) {
		buf[*ptr] = '0';
		*ptr += 1;
		i--;
	}

	i = (int)n_width;
	while (i-- > 0) {
		buf[*ptr] = "0123456789abcdef"[(value>>(i*4))&0xF];
		*ptr += + 1;
	}
}

int
vasprintf(char * buf, const char *fmt, __builtin_va_list args) {
	int i = 0;
	char *s;
	int ptr = 0;
	int len = strlen(fmt);
	for ( ; i < len && fmt[i]; ++i) {
		if (fmt[i] != '%') {
			buf[ptr++] = fmt[i];
			continue;
		}
		++i;
		unsigned int arg_width = 0;
		while (fmt[i] >= '0' && fmt[i] <= '9') {
			arg_width *= 10;
			arg_width += fmt[i] - '0';
			++i;
		}
		/* fmt[i] == '%' */
		switch (fmt[i]) {
			case 's': /* String pointer -> String */
				s = (char *)va_arg(args, char *);
				while (*s) {
					buf[ptr++] = *s++;
				}
				break;
			case 'c': /* Single character */
				buf[ptr++] = (char)va_arg(args, int);
				break;
			case 'x': /* Hexadecimal number */
				print_hex((unsigned long)va_arg(args, unsigned long), arg_width, buf, &ptr);
				break;
			case 'd': /* Decimal number */
				print_dec((unsigned long)va_arg(args, unsigned long), arg_width, buf, &ptr);
				break;
			case '%': /* Escape */
				buf[ptr++] = '%';
				break;
			default: /* Nothing at all, just dump it */
				buf[ptr++] = fmt[i];
				break;
		}
	}
	/* Ensure the buffer ends in a null */
	buf[ptr] = '\0';
	return ptr;

}

unsigned short * textmemptr = (unsigned short *)0xB8000;
// void placech(unsigned char c, int x, int y, int attr) {
// 	unsigned short *where;
// 	unsigned att = attr << 8;
// 	where = textmemptr + (y * 80 + x);
// 	*where = c | att;
// }

int x = 0, y = 0;
char color;
int _not_ready = 1;
int _off = 0;

void
gotoxy(
	int X,
	int Y
)
{
	x = X;
	y = Y;
}


int
kprintf(
		const char *fmt,
		...
	   ) {
	color = VGAGetColor();
	char buf[1024] = {-1};
	__builtin_va_list args;
	va_start(args, fmt);
	int out = vasprintf(buf, fmt, args);
	/* We're done with our arguments */
	va_end(args);
	/* Print that sucker */
	if (1) {
		/*
		 * VGA output for debugging. This is not nearly as feature-complete as the old
		 * kernel terminal; it is here to provide acceptable parsing of the debug messages
		 * and print them to the screen while in early boot on real hardware without a
		 * serial line and should not be used otherwise.
		 */
		if (_not_ready) {
			int temp = 0xFFFF;
			outb(0x3D4, 14);
			outb(0x3D5, temp >> 8);
			outb(0x3d4, 15);
			outb(0x3d5, temp);
			for (int y = 0; y < 80; ++y) {
				for (int x = 0; x < 25; ++x) {
					VGAPutEntry(' ', x, y, color);
				}
			}
			_not_ready = 0;
		}
		unsigned char *c = (unsigned char *)buf;
		while (*c) {
			if (_off) {
				if (*c > 'a' && *c < 'z') {
					_off = 0;
				} else {
					c++;
					continue;
				}
			} else if (*c == '\033') {
				c++;
				if (*c == '[') {
					_off = 1;
				}
			} else if (*c == '\n') {
				y += 1;
				x = 0;
			} else {
                VGAPutEntry(*c, x, y, color);
				x++;
			}
			if (x == 80) {
				x = 0;
				y++;
			}
			if (y > 25) {
				y--;
				x = 0;
				size_t sizescr = (25) * 80;
				memmove(textmemptr, textmemptr + 80, sizescr * 25);
				
				for (int k=1; k < 80; k++)
				{
					VGAPutEntry(' ', k, 25, color);
				}

				// memcpy(textmemptr + (80*25), textmemptr + (80), 80);
			}
			c++;
		}
	}
	/* Registered output file */
	return out;
}