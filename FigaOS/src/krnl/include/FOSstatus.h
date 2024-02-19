/** @file FOSstatus.h
 *  Copyright (c) 2023 FigaSystems
 *  FOS status definitions
 *  @author Daniil Dunaef
 *  @date 18-Dec-2023
 *  @bug No current bugs found
*/



#ifndef _FOS_STATUS_
#define _FOS_STATUS_

#define FOS_SUCCESS(Status) ((FOSSTATUS)(Status) >= 0)

#define STATUS_SUCCESS ((FOSSTATUS)0x00000000L)

#define STATUS_UNSUCCESSFUL ((FOSSTATUS)0xC0000001L)

typedef long FOSSTATUS;

#endif /* !_FOS_STATUS_! */