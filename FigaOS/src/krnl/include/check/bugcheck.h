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
 *  @param Code Code of error
 *  @param Message Error description
 *  @return Nothing
*/
FOSKERNELAPI 
VOID
BCPanic(
    IN ULONG Code,
    IN PCHAR Message
);

#endif /* !_BUGCHECK_! */