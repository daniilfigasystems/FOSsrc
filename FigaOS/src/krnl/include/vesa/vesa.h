/** @file vesa.h
 *  Copyright (c) 2023 FigaSystems
 *  VESA VBE functions for graphics
 *  @author Daniil Dunaef
 *  @date 21-Dec-2023
 *  @bug No current bugs found
*/



#ifndef _VESA_VBE_
#define _VESA_VBE_

#include "FOSdef.h"
#include "FOSstatus.h"

typedef ULONG VideoFrameBufferAddress;
typedef PULONG PVideoFrameBufferAddress;
typedef CHAR FontStart;
typedef PCHAR PFontStart;
typedef CHAR FontEnd;
typedef PCHAR PFontEnd;
typedef CHAR FontSize;
typedef PCHAR PFontSize;

typedef struct _VideoInformation
{
    ULONG FrameBufferAddress;
    UINT FrameBufferPitch;
    UINT FrameBufferWidth;
    UINT FrameBufferHeight;
    UCHAR FrameBufferBPP;
    UCHAR FrameBufferType;
} VideoInformation;

/** @brief Init VBE Video graphics buffer
 *  @param VideoFrameBuffer Framebuffer of video graphics
 *  @param VideoPitch Video Pitch
 *  @param VideoWidth Video Width
 *  @param VideoHeight Video Height
 *  @param VideoBPP Video BPP
 *  @param VideoType Video Type
 *  @return STATUS_SUCCESS if video buffer was initialized successfully STATUS_UNSUCCESSFUL if video buffer was not initialized
*/
FOSSYSAPI
FOSSTATUS
InbvInitVideoBuffer(
    IN PVideoFrameBufferAddress VideoFrameBuffer,
    IN UINT VideoPitch,
    IN UINT VideoWidth,
    IN UINT VideoHeight,
    IN UCHAR VideoBPP,
    IN UCHAR VideoType
);

FOSSYSAPI
VOID
InbvPixPlt(
    IN INT X,
    IN INT Y,
    IN LONG Color
);

FOSSYSAPI
VOID
InbvFillRect(
    IN INT StartX,
    IN INT StartY,
    IN INT X,
    IN INT Y,
    IN LONG Color
);

FOSSYSAPI
VOID
InbvLoadPSFFont(
    void
);

FOSSYSAPI
VOID
InbvDrawCharacter(
    unsigned short int Character,
    INT CharacterX, 
    INT CharacterY,
    UINT ForeGround,
    UINT BackGround
);

#endif /* !_VESA_VBE_! */