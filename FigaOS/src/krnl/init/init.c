/** @file init.c
 *  Copyright (c) 2023 FigaSystems
 *  Initialization
 *  @author Daniil Dunaef
 *  @date 15-Nov-2023
 *  @bug No current bugs found
*/


#include "gdt/gdt.h"

int k_main()
{
    GDTInstall(gp);
}