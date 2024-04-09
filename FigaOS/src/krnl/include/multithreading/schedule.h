#include "FOSdef.h"
#include "regs/regs.h"

typedef 
struct 
_Thread
{
    regs registers;
    BOOL islocked;
    int tid;
} Thread;

struct context;

void MTCreateThread(void *address);

void MTSwitchTo(int tid);