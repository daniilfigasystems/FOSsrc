
#ifndef _string_
#define _string_

extern int memcpy(char *src, char *dest, int nbytes);

extern int memset(char *dest, char c, int nbytes);

extern int strcpy(char *dest, char *src);

extern int strlen(const char* str);
#endif