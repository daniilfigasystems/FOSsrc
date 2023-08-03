#include "../../ntos/include/ntoskrnl.h"
enum videomodes {
   VIDEO_TYPE_NONE = 0x00,
   VIDEO_TYPE_COLOUR = 0x20,
   VIDEO_TYPE_MONO = 0x30,
};
uint16 detect_bios_area_hardware(void)
{
    const uint16* bda_detected_hardware_ptr = (const uint16*) 0x410;
    return *bda_detected_hardware_ptr;
}
 
uint16 get_bios_area_video_type(void)
{
    return (enum videomodes) (detect_bios_area_hardware() & 0x30);
}