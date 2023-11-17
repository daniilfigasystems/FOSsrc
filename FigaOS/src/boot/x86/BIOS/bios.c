/** @file bios.c
 *  Copyright (c) 2023 FigaSystems
 *  Bios interrupts and other bios related functions
 *  @author Daniil Dunaef
 *  @date 15-Nov-2023
 *  @bug No current bugs found
*/



#include "BIOS/bios.h"

extern 
void 
to_pm(
    void
    );

extern
void
checkA20(
    void
    );

void 
cli(
    void
    )
{
    asm volatile ("cli");
}

void 
sti(
    void
    )
{
    asm volatile ("sti");
}

void 
switch_to_PM(
    void
    )
{
    to_pm();
}