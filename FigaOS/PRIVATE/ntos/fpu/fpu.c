#include "fpu.h"
#include "asm.h"
#include "serial.h"
extern unsigned int testfpu();
void checkfpu() {
    int testval = testfpu();
    if (testval == 0) {
        write_com(0x3f8, " NO FPU!");
        halt();
    }
    else {
        write_com(0x3f8, " FPU Present!");
    }
}
void fpu_load_control_word(const unsigned short control)
{
    asm volatile("fldcw %0;"::"m"(control)); 
}                                                                    
                                                                