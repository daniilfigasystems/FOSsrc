#include "irq/irq.h"

void ISRInstall(int isrs, void* handler);

void ISRUninstall(int isrs);


void ISRInitialize();
void ISRHandler(struct irqr* r);