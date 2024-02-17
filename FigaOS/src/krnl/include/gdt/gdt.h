/** @file gdt.h
 *  Copyright (c) 2023 FigaSystems
 *  Global descriptor table
 *  @author Daniil Dunaef
 *  @date 16-Nov-2023
 *  @bug No current bugs found
*/



#ifndef _GDT_
#define _GDT_

#include "FOSdef.h"

struct gdt_entry
{
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char limit_middle;
    unsigned char base_middle;
    unsigned char access;
    unsigned int read_write;
    unsigned int code;
    unsigned int code_data_seg;
    unsigned int confortming_ex_d;
    unsigned int DPL;
    unsigned short present;
    unsigned int available;
    unsigned char granularity;
    unsigned char limit_high;
    unsigned char base_high;
} __attribute__((packed));

struct gdt_pointer
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

/** @brief Load Global descriptor table
 *  @param num Number of Global descriptor table
 *  @param base Base address
 *  @param limit Limit of address
 *  @param access Access to Global descriptor table
 *  @param granularity Global descriptor table granularity
 *  @return Nothing
*/
FOSKERNELAPI
VOID
GDTSetGate(
    int num, 
    unsigned long base, 
    unsigned long limit, 
    unsigned char access, 
    unsigned char granularity
);

/** @brief Load Global descriptor table
 *  @param void Nothing
 *  @return Nothing
*/
FOSKERNELAPI
VOID
GDTInstall(
    void
);

#endif