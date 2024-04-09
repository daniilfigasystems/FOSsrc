#include "irq/irq.h"

void ISRInstall(int isrs, void* handler);

void ISRUninstall(int isrs);


void ISRInit();
void ISRHandle(struct irqr* r);