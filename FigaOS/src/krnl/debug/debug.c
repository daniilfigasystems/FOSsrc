#include "debug/debug.h"
#include "misc/kprintf.h"

void 
DBGStackTrace(
    unsigned int MaxFrames
)
{
    StackFrame *stk;
    asm ("movl %%ebp,%0" : "=r"(stk) ::);
    kprintf("Stack trace:\n");
    for(unsigned int frame = 0; stk && frame < MaxFrames; ++frame)
    {
        // Unwind to previous stack frame
        kprintf("  0x%x     \n", stk->eip);
        stk = stk->ebp;
    }
}