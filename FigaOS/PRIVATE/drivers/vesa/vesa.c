typedef struct regs
{
    unsigned int gs, fs, es, ds;      
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  
    unsigned int int_no, err_code;    
    unsigned int eip, cs, eflags, useresp, ss;   
    unsigned int ax, al, dx, cx;
    unsigned int bl, bh, bx;
    unsigned int di; 
};
struct regs r;
struct ModeInfoBlock {
unsigned short attributes;
unsigned char winA,winB;
unsigned short granularity;
unsigned short winsize;
unsigned short segmentA, segmentB;
unsigned short pitch; // bytes per scanline
 
unsigned short Xres, Yres;
unsigned char Wchar, Ychar, planes, bpp, banks;
unsigned char memory_model, bank_size, image_pages;
unsigned char reserved0;
 
unsigned char red_mask, red_position;
unsigned char green_mask, green_position;
unsigned char blue_mask, blue_position;
unsigned char rsv_mask, rsv_position;
unsigned char directcolor_attributes;
 
unsigned int physbase; // your LFB (Linear Framebuffer) address  ;) the new address of screen.
unsigned int reserved1;
unsigned short reserved2;
} __attribute__((packed));
void vesa_init() 
{
    r.eax = 0x4F02;
    r.ebx = 0x118;
    int32(0x10, &r);
    write_com(0x3f8, " vesa initializated");
}
