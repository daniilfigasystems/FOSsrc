#include "timers/pit/pit.h"
#include "timers/pic/pic.h"
#include "irq/irq.h"
#include "io/io.h"
#include "misc/kprintf.h"

int ticks = 0;
unsigned long ticker = 0;

void handle_timer(
    void
)
{
	ticks++;

	if (ticks % 18 == 0)
	{
		ticker++;
	}
}

void PITInit(
    unsigned int frequency
)
{
    IRQInstall(0, handle_timer);
    PICRemap();
	int div = 1193180 / frequency;

	outb(0x43, 0x36);
	outb(0x40, div & 0xFF);
	outb(0x40, (div >> 8) & 0xFF);
}


void wait(
    int wait_ticks
)
{
	unsigned long eticks;
	eticks = ticks + wait_ticks;

	while (ticks < eticks);
}