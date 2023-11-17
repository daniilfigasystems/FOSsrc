/** @file vga.c
 *  Copyright (c) 2023 FigaSystems
 *  VGA related functions
 *  @author Daniil Dunaef
 *  @date 15-Nov-2023
 *  @bug No current bugs found
*/



#include "vga/vga.h"

char* vmem;

void
VGA_init(
    void
    )
{
	vmem = (char *)VIDEO_ADDRESS;
	unsigned int i=0;
	while (i < (80*25*2)) {
		vmem[i] = 'd';
		i++;
		vmem[i] = 0x17;
		i++;
    }
}