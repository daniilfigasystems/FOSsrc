/** @file bugcheck.c
 *  Copyright (c) 2023 FigaSystems
 *  Bug tracing and death screen functions
 *  @author Daniil Dunaef
 *  @date 17-Dec-2023
 *  @bug No current bugs found
*/



#include "check/bugcheck.h"
#include "FOSdef.h"
#include "check/bugcodes.h"
#include "vga/vga.h"

FOSKERNELAPI 
VOID
KeBugCheck(
    IN ULONG BugCheckCode
)
{
    // If you are getting death screen, dont worry this happens to everyone
    switch(BugCheckCode)
    {
        case FATAL_UNHANDLED_KERNEL_EXPECTION:
    }
}