/** @file vga.h
 *  Copyright (c) 2023 FigaSystems
 *  Vga graphics functions
 *  @author Daniil Dunaef
 *  @date 15-Nov-2023
 *  @bug No current bugs found
*/



#ifndef _VGA_
#define _VGA_

#define VIDEO_ADDRESS 0xB8000

typedef enum {
    COLOR_BLACK,
    COLOR_BLUE,
    COLOR_GREEN,
    COLOR_CYAN,
    COLOR_RED,
    COLOR_MAGENTA,
    COLOR_BROWN,
    COLOR_GREY,
    COLOR_DARK_GREY,
    COLOR_BRIGHT_BLUE,
    COLOR_BRIGHT_GREEN,
    COLOR_BRIGHT_CYAN,
    COLOR_BRIGHT_RED,
    COLOR_BRIGHT_MAGENTA,
    COLOR_YELLOW,
    COLOR_WHITE,
} VGA_COLOR_TYPE;

/** @brief VGA Get item entry
 *  @param ch Character to get
 *  @param fore_color Forgeground color
 *  @param back_color Background color
 *  @return Nothing
*/
unsigned 
short 
VGAItemEntry(
	unsigned char ch, 
	VGA_COLOR_TYPE fore_color, 
	VGA_COLOR_TYPE back_color
);

/** @brief VGA Clear screen
 *  @param void Nothing
 *  @return Nothing
*/
void
VGAInit(
    void
);

/** @brief VGA Put character on xy position with specified color
 *  @param entry Character to put
 *  @param colorbg Background Color of character
 *  @param colorfg Foreground Color of character
 *  @return Nothing
*/
void
VGAPutEntry(
	char entry,
	int color,
    int x,
    int y
);

/** @brief VGA Put string on xy position with specified color
 *  @param str String to put
 *  @param colorbg Background Color of character
 *  @param colorfg Foreground Color of character
 *  @return Nothing
*/
void 
VGAPrintString( 
	char *str, 
    int x,
    int y,
    int color
);

void
VGANewLine(
	void
);

void
VGASetColor(
	int color
);

int
VGAGetColor(
	void
);

void
VGASetVideoMode(
	void
);

#endif