/** @file bugcheck.h
 *  Copyright (c) 2023 FigaSystems
 *  Bug tracing and death screen functions
 *  @author Daniil Dunaef
 *  @date 18-Dec-2023
 *  @bug No current bugs found
*/



#ifndef _BUGCHECK_
#define _BUGCHECK_

#include "FOSdef.h"
#include "bugcodes.h"

/** @brief Displaying death screen and halts system
 *  @param BugCheckCode Code of error
 *  @return Nothing
*/
FOSKERNELAPI
VOID
KeBugCheck(
    IN ULONG BugCheckCode
);

#endif /* !_BUGCHECK_! */