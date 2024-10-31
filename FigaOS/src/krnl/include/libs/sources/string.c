/** @file string.c
 *  Copyright (c) 2023 FigaSystems
 *  String operations
 *  @author Daniil Dunaef
 *  @date 14-Nov-2023
 *  @bug No current bugs found
*/



#include "libs/headers/string.h"

unsigned 
int
memcpy(
	void *dst, 
	void *src, 
	size_t count
)
{
	const unsigned char *a = src;
	unsigned char *b = dst;
	if (src == 0)
	{
		return 0;
	}
	else if ((unsigned long)dst < (unsigned long)src)
	{
		for (size_t i = 0; i < count; ++i)
		{
			b[i] = a[i];
		}
		return (unsigned int) b;
	}
	else if ((unsigned long)dst > (unsigned long)src)
	{
		for (int i = count; i > 0; --i)
		{
			b[i-1] = a[i-1];
		}
		return (unsigned int) b;
	}
	return 0;
}

int 
max(
	int a, 
	int b
) 
{
	return (a > b) ? a : b;
}

int 
min(
	int a, 
	int b
) 
{
	return (a > b) ? b : a;
}

int 
abs(
	int a
) 
{
	return (a >= 0) ? a : -a;
}

void 
swap(
	int *a, 
	int *b
) 
{
	int t = *a;
	*a = *b;
	*b = t;
}

void 
* 
memmove(
	void * restrict dest, 
	void * restrict src, 
	unsigned int count
) 
{
	unsigned int i;
	unsigned long *a = dest;
	unsigned long *b = src;
	if (src < dest) 
	{
		for ( i = count; i > 0; --i) 
		{
			a[i-1] = b[i-1];
			b[i] = 0;
		}
	} else 
	{
		for ( i = 0; i < count; ++i) 
		{
			a[i] = b[i];
			b[i] = 0;
		}
	}
	return dest;
}

int 
atoi (
	const char * str
) 
{
  int value = 0;
  while(str != 0)  
  {
    value *= 10;
    value += (*str)-'0';
    str++;
  }

  return value;
}
char
* 
itoa(
	int res
) 
{
    int size = 0;
    int t = res;

    while(t / 10 != 0) 
	{
        t = t/10;
        size++;
    }
    static char ret[64];
    size++;
    ret[size] = '\0';
    t = res;
    int i = size - 1;
    while(i >= 0) 
	{
        ret[i] = (t % 10) + '0';
        t = t/10;
        i--;
    }

    return ret;
}

int 
strcmp(
	const char * a, 
	const char * b
) 
{
	for (unsigned int i = 0; i < sizeof(a); i++) 
	{
		if (a[i] < b[i]) 
		{
			return -1;
		} else if (a[i] > b[i]) 
		{
			return 1;
		} else 
		{
			if (a[i] == '\0' || b[i] == '\0') 
			{
				return 0;
			}
		}
	}
	return 0;
}

void
*
memset(
	void* dst,
	int val, 
	size_t count
)
{
	unsigned char *a = dst;
	if (count == 0)
	{
		return 0;
	}
	for (unsigned int i = 0; i < count; ++i)
	{
		a[i] = val;
	}
	return a;
}


unsigned short * memsetw(unsigned short * dest, unsigned short val, int count) {
	for (int i = 0; i < count; ++i ) {
		dest[i] = val;
    }
	return dest;
}

unsigned int 
strlen(
	const char *str
) 
{
	int i = 0;
	while (str[i] != (char)0 || str[i] != '\0') 
	{ 
		++i;
	}
	return i;
}
