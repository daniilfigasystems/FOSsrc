


#include "FOSdef.h"
#include "FOSstatus.h"

typedef enum _KeybLedState
{
    ScrollLock = 0,
    NumberLock = 1,
    CapsLock = 2,
} KeybLedState;

FOSSYSAPI
FOSSTATUS
KeybInitializeKeyboardPS2(
    void
);

FOSSYSAPI
VOID 
KeybTurnOnLED(
    KeybLedState LEDNum
);

FOSSYSAPI
UCHAR
KeybGetKeyChar(
    void
);

FOSSYSAPI
INT
KeybGetKeyCode(
    void
);

FOSSYSAPI
VOID
KeybResetCPU(
    void
);