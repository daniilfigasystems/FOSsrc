/** @file io.h
 *  Copyright (c) 2023 FigaSystems
 *  Inport and outport functions
 *  @author Daniil Dunaef
 *  @date 1-Dec-2023
 *  @bug No current bugs found
*/

#ifndef _IO_
#define _IO_

static 
inline 
void 
outb(
    unsigned short port, 
    unsigned char val
)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) : "memory");
}

static 
inline 
void 
outw(
    unsigned short port, 
    unsigned short val
)
{
    asm volatile ( "outw %0, %1" : : "a"(val), "Nd"(port) : "memory");
}

static 
inline 
void 
outl(
    unsigned short port, 
    unsigned int val
)
{
    asm volatile ( "outl %0, %1" : : "a"(val), "Nd"(port) : "memory");
}

static 
inline 
unsigned 
char 
inb(
    unsigned short port
)
{
    unsigned char ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}

static 
inline 
unsigned 
short
inw(
    unsigned short port
)
{
    unsigned short ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}

static 
inline 
unsigned 
int 
inl(
    unsigned short port
)
{
    unsigned int ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}

#endif /* !_IO_! */