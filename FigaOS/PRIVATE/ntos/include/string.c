void * memcpy(void * restrict dest, const void * restrict src, unsigned int count) {
	asm volatile ("cld; rep movsb" : "+c" (count), "+S" (src), "+D" (dest) :: "memory");
	return dest;
}

int max(int a, int b) {
	return (a > b) ? a : b;
}

int min(int a, int b) {
	return (a > b) ? b : a;
}

int abs(int a) {
	return (a >= 0) ? a : -a;
}

void swap(int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}

void * memmove(void * restrict dest, const void * restrict src, unsigned int count) {
	unsigned int i;
	unsigned char *a = dest;
	const unsigned char *b = src;
	if (src < dest) {
		for ( i = count; i > 0; --i) {
			a[i-1] = b[i-1];
		}
	} else {
		for ( i = 0; i < count; ++i) {
			a[i] = b[i];
		}
	}
	return dest;
}

int strcmp(const char * a, const char * b) {
	unsigned int i = 0;
	while (1) {
		if (a[i] < b[i]) {
			return -1;
		} else if (a[i] > b[i]) {
			return 1;
		} else {
			if (a[i] == '\0') {
				return 0;
			}
			++i;
		}
	}
}


void * memset(void * b, int val, unsigned int count) {
	asm volatile ("cld; rep stosb" : "+c" (count), "+D" (b) : "a" (val) : "memory");
	return b;
}


unsigned short * memsetw(unsigned short * dest, unsigned short val, int count) {
	int i = 0;
	for ( ; i < count; ++i ) {
		dest[i] = val;
	}
	return dest;
}

/*
 * strlen
 * Returns the length of a given `str`.
 */
unsigned int strlen(const char *str) {
	int i = 0;
	while (str[i] != (char)0) {
		++i;
	}
	return i;
}
