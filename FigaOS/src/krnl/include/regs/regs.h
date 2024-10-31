#ifndef _REGS_
#define _REGS_

typedef
struct _regs
{
    int edi,
        esi,
        ebp,
        esp,
        ebx,
        edx,
        ecx,
        eax,
        eip;
    int int_no;
    int err_code;
    int eflags;
} regs;

void __dump_dummy__(regs registers);
void dump();
regs getregs();

#endif /* !_REGS_! */