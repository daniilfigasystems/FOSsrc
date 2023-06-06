//     Figa Systems //
// VGA DRIVER //
#define VIDEO_MEM (0x8000)
#define VIDEO_MEM_SIZE_HIGH (0x8000)
#define VIDEO_MEM_SIZE_LOW (0x0)
#define VIDEO_MEM_SIZE_TOTAL (VIDEO_MEM_SIZE_HIGH + VIDEO_MEM_SIZE_LOW + VIDEO_MEM)
#define VGA_WIDTH 320
#define VGA_HEIGHT 200
#define VGA_SIZE (VGA_WIDTH * VGA_HEIGHT)
#define VGA_COLORS 8
#define VGA_COLOR_BLACK 0
#define VGA_COLOR_WHITE 1
#define VGA_COLOR_RED 2
#define VGA_COLOR_GREEN 3
#define VGA_COLOR_BLUE 4
#define VGA_COLOR_YELLOW 5
#define VGA_COLOR_MAGNETA 6
#define VGA_COLOR_CYAN 7
#define default_video_memory (VIDEO_MEM + VGA_WIDTH * VGA_HEIGHT)
#define default_video_memory_size (4096)
#define BufferColorDark (0x0000ff)
#include "ports.c"

function ;void io_in(int port, int word) {
    outportb(port, word);
}
function ;void io_out(int port, int word) {
    inportb(port, word);
    }

function ;void vga_init(void) {

unsigned int i;
for (i = 0; i < VGA_SIZE; i++) 
{
int cbuffer = {0, 1, 2, 3, 4, 5, 6, 7};
cbuffer = VGA_COLOR_BLACK;
}
}
function ;void vga_set_video_mode(char *mode) {
    inportb(0x3d4, mode);

}
function ;void vga_clear(void) {
   unsigned int i;
    for (i = 0; i < VGA_SIZE; i++) {
        int cbuffer = {0, 1, 2, 3, 4, 5, 6, 7};
        cbuffer = (BufferColorDark);
    }
}
function ;void print_char(char *print, unsigned int *line) {
unsigned int i;
if (print = '\n') {
    *line = *line + 1;
    VIDEO_MEM == print++;
    *print++;
}
else {
VIDEO_MEM == print;
*print++;
}
}
int main(void) {
    vga_init();
    vga_set_video_mode("text");
    vga_clear();
    print_char("Hello World!", default_video_memory);
}