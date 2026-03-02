#include "fsl_device_registers.h"

void delay(void) {
    for (volatile int i = 0; i < 1000000; i++) __asm("nop");
}

int main(void) {
    WWDT0->MOD = 0x00;

    SYSCON->AHBCLKCTRLSET[0] = (1 << 13) | (1 << 14) | (1 << 19) | (1 << 20);

    // configureaza pinii ca GPIO
    PORT0->PCR[10] = 0x1000;
    PORT0->PCR[27] = 0x1000;
    PORT1->PCR[2]  = 0x1000;

    // pinii ca iesire
    GPIO0->PDDR |= (1 << 10) | (1 << 27);
    GPIO1->PDDR |= (1 << 2);

    while (1) {
        GPIO0->PTOR = (1 << 10);
        delay();
        GPIO0->PTOR = (1 << 27);
        delay();
        GPIO1->PTOR = (1 << 2);
        delay();
    }

    return 0;
}