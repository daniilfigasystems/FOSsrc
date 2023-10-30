#include "hal.h"
#include "serial.h"
#include "sb16.h"
void reset_DSP() 
{
    outb(0x226, 1);
    iowait();
    outb(0x226, 0);
   if (inb(0x22A) == 0xAA) 
   {
    write_com(COM1, module_name);
    write_com(COM1, " Reseted DSP! ");
   }
}
void set_mode(char mode, int pagenum, int length, char ch) 
{
    switch(mode) 
    {
        SBMODE8_1CH_AUTO:
        outb(0x0A, 0x05);
        outb(0x0C, 1);
        outb(0x0B, 0x58 + ch);
        outb(0x83, pagenum)
        outb(0x02, 0x50);
        outb(0x02, 0x04);
        outb(0x03, length & 0xFFFF);
        outb(0x03, (length >> 24) & 0xFFFF);
        outb(0x0A, ch);
        break;
        SBMODE8_1CH_SINGLE:
        outb(0x0A, 0x05);
        outb(0x0C, 1);
        outb(0x0B, 0x48 + ch);
        outb(0x83, pagenum)
        outb(0x02, 0x50);
        outb(0x02, 0x04);
        outb(0x03, length & 0xFFFF);
        outb(0x03, (length >> 24) & 0xFFFF);
        outb(0x0A, ch);
        break;
        SBMODE16_5CH_AUTO:
        outb(0xD4, 0x05);
        outb(0xD8, 1);
        outb(0xD6, 0x58 + ch);
        outb(0x8B, pagenum);
        outb(0xC4, 0x50);
        outb(0xC4, 0x04);
        outb(0xC6, length & 0xFFFF);
        outb(0xC6, (length >> 24) & 0xFFFF);
        outb(0xD4, ch);
        break;
        SBMODE16_5CH_SINGLE:
        outb(0xD4, 0x05);
        outb(0xD8, 1);
        outb(0xD6, 0x48 + ch);
        outb(0x8B, pagenum);
        outb(0xC4, 0x50);
        outb(0xC4, 0x04);
        outb(0xC6, length & 0xFFFF);
        outb(0xC6, (length >> 24) & 0xFFFF);
        outb(0xD4, ch);
        break;
    }
    /* if (mode == SBMODE8_1CH_AUTO)
    {
        outb(0x0A, 0x05);
        outb(0x0C, 1);
        outb(0x0B, 0x58 + ch);
        outb(0x83, pagenum)
        outb(0x02, 0x50);
        outb(0x02, 0x04);
        outb(0x03, length & 0xFFFF);
        outb(0x03, (length >> 24) & 0xFFFF);
        outb(0x0A, ch);
    }
    else if (mode == SBMODE8_1CH_SINGLE)
    {
        outb(0x0A, 0x05);
        outb(0x0C, 1);
        outb(0x0B, 0x48 + ch);
        outb(0x83, pagenum)
        outb(0x02, 0x50);
        outb(0x02, 0x04);
        outb(0x03, length & 0xFFFF);
        outb(0x03, (length >> 24) & 0xFFFF);
        outb(0x0A, ch);
    }
    else if (mode == SBMODE16_5CH_AUTO)
    {
        outb(0xD4, 0x05);
        outb(0xD8, 1);
        outb(0xD6, 0x58 + ch);
        outb(0x8B, pagenum);
        outb(0xC4, 0x50);
        outb(0xC4, 0x04);
        outb(0xC6, length & 0xFFFF);
        outb(0xC6, (length >> 24) & 0xFFFF);
        outb(0xD4, ch);
    }
    else if (mode == SBMODE16_5CH_SINGLE)
    {
        outb(0xD4, 0x05);
        outb(0xD8, 1);
        outb(0xD6, 0x48 + ch);
        outb(0x8B, pagenum);
        outb(0xC4, 0x50);
        outb(0xC4, 0x04);
        outb(0xC6, length & 0xFFFF);
        outb(0xC6, (length >> 24) & 0xFFFF);
        outb(0xD4, ch);
    } */
}
void Set_Speaker_Mode(int speakermode)
{
    switch(speakermode)
    TURN_ON_SPK_SB16:
    outb(0x22C, 0xD1);
    break;
    TURN_OFF_SPK_SB16:
    outb(0x22C, 0xD3);
}
void set_volume_SB16(int volume, char lr)
{
    switch(lr) 
    {
        LEFT_SB16:
        outb(0x22, 0x0 + volume);
        break;
        RIGHT_SB16:
        outb(0x22, 0xF0 + volume);
        break;
    }
}
void init_SB16(SB16_DEVICE *sinit, char l, char r, int vol, int spkmode, char mode, int pgnum) 
{
    outb(0x224, 0x80);
    outb(0x225, 0x08);
    write_com(COM1, module_name);
    write_com(COM1, " init_SB16() initialization ");
}