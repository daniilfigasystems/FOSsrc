#include "vesa/vesa.h"
#include "vesa/font.h"
#include "libs/headers/string.h"
#include "FOSdef.h"
#include "FOSstatus.h"

PVideoFrameBufferAddress VBEAddress;
VideoInformation VBEInformation;

USHORT *UniCode;

FOSSYSAPI
FOSSTATUS
InbvInitVideoBuffer(
    IN PVideoFrameBufferAddress VideoFrameBuffer,
    IN UINT VideoPitch,
    IN UINT VideoWidth,
    IN UINT VideoHeight,
    IN UCHAR VideoBPP,
    IN UCHAR VideoType
)
{
    FOSSTATUS Status = STATUS_UNSUCCESSFUL;

    if (VideoFrameBuffer != NULL || VideoFrameBuffer != 0)
    {
        VBEAddress = VideoFrameBuffer;

        VBEInformation.FrameBufferPitch = VideoPitch;
        VBEInformation.FrameBufferWidth = VideoWidth;
        VBEInformation.FrameBufferAddress = VideoFrameBuffer;
        VBEInformation.FrameBufferType = VideoType;
        VBEInformation.FrameBufferHeight = VideoHeight;
        VBEInformation.FrameBufferBPP = VideoBPP;

        Status = STATUS_SUCCESS;

        return Status;
    }
    else
    {
        Status = STATUS_UNSUCCESSFUL;

        return Status;
    }

    return Status;
}

FOSSYSAPI
VOID
InbvPixPlt(
    IN INT X,
    IN INT Y,
    IN LONG Color
)
{
    INT VBEPosition = (X*Y);

    PVideoFrameBufferAddress VBEAddressPointer = VBEAddress;

    VBEAddress[VBEPosition] = Color;
}

FOSSYSAPI
VOID
InbvFillRect(
    IN INT StartX,
    IN INT StartY,
    IN INT X,
    IN INT Y,
    IN LONG Color
)
{
    PVideoFrameBufferAddress VBEAddressPointer = VBEAddress;

    INT StartPosition = (StartX*StartY);
    INT VBEPosition = (X*Y) + StartPosition;

    for (int i = StartX; i < StartX + X; i++)
    {
	    for (int j = StartY * 1024; j <  StartY * 1024 + Y; j++)
            VBEAddressPointer[j + StartX] = Color;
        VBEAddressPointer += 1024;
    }
}

FOSSYSAPI
VOID
InbvLoadPSFFont(
    void
)
{
    // USHORT Glyph = 0;

    // PSF_font *Font = (PSF_font *)&_binary_src_fonts_ter_powerline_v28b_psf_start;

    // if (Font->flags)
    // {
    //     UniCode = NULL;
    //     return;
    // }

    // PCHAR S = (PCHAR)(
    //     (PUCHAR)&_binary_src_fonts_ter_powerline_v28b_psf_start +
    //     Font->headersize +
    //     Font->numglyph * Font->bytesperglyph
    // );

    // UniCode = 2;

    // while (S < _binary_src_fonts_ter_powerline_v28b_psf_end)
    // {
    //     USHORT UC = (USHORT)((PUCHAR)S[0]);

    //     if (UC == 0xFF)
    //     {
    //         Glyph++;
    //         S++;
    //         continue;
    //     }
    //     else if (UC & 128)
    //     {
    //         if ((UC & 32) == 0)
    //         {
    //             UC = ((S[0] & 0X1F) << 6) + (S[1] & 0X3F);
    //             S++;
    //         }
    //         else if ((UC & 16) == 0)
    //         {
    //             UC = ((((S[0] & 0X1F) << 6) + (S[1] & 0X3F)));
    //             S += 2;
    //         }
    //         else if ((UC & 8) == 0)
    //         {
    //             UC = ((((S[0] & 0X7) << 6) + (S[1] & 0X3F) << 6) + (S[2] & 0X3F));
    //             S += 3;
    //         }
    //         else
    //             UC = 0;
    //     }

    //     UniCode[UC] = Glyph;
    //     S++;
    // }
}

FOSSYSAPI
VOID
InbvDrawCharacter(
    unsigned short int Character,
    INT CharacterX, 
    INT CharacterY,
    UINT ForeGround,
    UINT BackGround
)
{
    // PSF_font *Font = (PSF_font*)&_binary_src_fonts_ter_powerline_v28b_psf_start;

    // INT BytesPerLine = (Font->width + 7) / 8;

    // PVideoFrameBufferAddress VBEAddressPointer = VBEAddress;

    // if (UniCode != NULL)
    // {
    //     Character = UniCode[Character];
    // }

    // UCHAR *Glyph = (PUCHAR)&_binary_src_fonts_ter_powerline_v28b_psf_start +
    // Font->headersize +
    // (Character > 0 && Character < Font->numglyph ? Character : 0) * Font->bytesperglyph;

    // int offs = VBEInformation.FrameBufferPitch;// (CharacterY * Font->height * (UINT)VBEAddressPointer) +
    // // (CharacterX * (Font->width + 1) * sizeof(UINT));

    // INT 
    // X, 
    // Y, 
    // Line;
    // UINT
    // Mask,
    // LineBits;

    // for (Y = 0; Y < Font->height; Y++)
    // {
    //     Line = offs;
    //     Mask = 1 << (Font->width - 1);

    //     for (X = 0; X < Font->width - 1; X++)
    //     {
    //         memcpy(&LineBits, VBEAddressPointer + Line, sizeof(UINT));
    //         *((PUINT)(VBEAddressPointer + Line)) = (LineBits & Mask) ? ForeGround : BackGround;

    //         Mask >>= 1;
    //         Line += sizeof(UINT);
    //     }

    //     Glyph += BytesPerLine;
    //     offs += VBEInformation.FrameBufferPitch; 
    // }
}