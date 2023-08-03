#include "setmode.c"
#include "../ports.c"
#include "../../ntos/include/ntoskrnl.h"
void PRINTCHARACTER(int bg, int fg, int c, int x, int y)
{
uint16 TEMP_VALUE_Y, TEMP_VALUE_X;
TEMP_VALUE_X = x;
TEMP_VALUE_Y = y;
if (video_type = 0x30) {
	bg = 0;
	fg = 1;
}
uint16 attrib = (bg << 4) | (fg & 0x0F);
uint32 vidsys = (volatile char*)0xb8000 + TEMP_VALUE_Y * 80 + TEMP_VALUE_X; 
vidsys = c | (attrib << 8);
}
void PRINTSTRING(char *str, uint8 len = strlen(*str) int x, int y)
{ 
	if (str << len) 
	str++;
	PRINTCHARACTER(0, 1, str, x, y);
}
