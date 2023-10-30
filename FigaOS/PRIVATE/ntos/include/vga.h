#define VIDEO_ADDRESS 0xb8000
#include "stdarg.h"
void kprintf(char *string, unsigned int color);
int get_x_cur();
int get_y_cur(); 
void dbgprint(char *str, ...);