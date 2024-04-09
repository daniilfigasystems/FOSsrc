#include "multithreading/schedule.h"
#include "regs/regs.h"

Thread threads[1024]; // max 1024 threads

int current_tid = 0;

void MTCreateThread(void *address)
{
    if (current_tid >= 1024)
        return;
    current_tid++;
    threads[current_tid].tid = current_tid;
    threads[current_tid].islocked = false;
    threads[current_tid].registers.eip = address;
}

void MTSwitchTo(int tid)
{
    if (threads[tid].islocked == true)
        return;

    dump();
    int eip = threads[current_tid].registers.eip;
    threads[current_tid].registers = getregs();
    threads[current_tid].registers.eip = eip;

    // asm volatile ("mov $., %0" : "=r" (threads[tid].eip));

    current_tid = tid;

    void *address = threads[tid].registers.eip;
    asm volatile("sti");
    goto *address;
}