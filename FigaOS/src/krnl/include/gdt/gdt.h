/** @file gdt.h
 *  Copyright (c) 2023 FigaSystems
 *  Global descriptor table
 *  @author Daniil Dunaef
 *  @date 16-Nov-2023
 *  @bug No current bugs found
*/



#ifndef _GDT_
#define _GDT_

struct gdt_entry
{
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char limit_middle;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char limit_high;
    unsigned char base_high;
} __attribute__((packed));

struct gdt_pointer
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct gdt_entry gdt[3];
struct gdt_pointer gp;

/** @brief Load Global descriptor table
 *  @param num Number of Global descriptor table
 *  @param base Base address
 *  @param limit Limit of address
 *  @param access Access to Global descriptor table
 *  @param granularity Global descriptor table granularity
 *  @return Nothing
*/
void 
GDTSetGate(
    int num, 
    unsigned long base, 
    unsigned long limit, 
    unsigned char access, 
    unsigned char granularity
    );

/** @brief Load Global descriptor table
 *  @param gp Pointer to global descriptor table
 *  @return Nothing
*/
void 
GDTInstall(
    struct gdt_pointer gp
    );

#endif