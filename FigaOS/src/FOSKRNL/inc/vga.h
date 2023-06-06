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
#define SET_VIDEO_MODE(x) outportb(0x3d4, (inportb(0x3d4) & 0xe0) | (x))
#define SER_VIDEO_HORIZONTAL(x) outportb (0x3d4, (inportb(0x3d4) & ) | (x))