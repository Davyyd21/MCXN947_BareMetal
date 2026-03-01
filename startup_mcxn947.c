#define CPU_MCXN947VDF_cm33_core0
#include "fsl_device_registers.h"
#include <stdint.h>

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _stack_top;

void Reset_Handler(void) __attribute__((naked, noreturn));
void SystemInit(void);
void Default_Handler(void) { while (1); }
extern int main(void);

__attribute__((section(".isr_vector"), used))
const uint32_t vectors[] = {
    (uint32_t)&_stack_top,        /* 0: Initial Stack Pointer */
    (uint32_t)Reset_Handler,      /* 1: Reset Handler */
    (uint32_t)Default_Handler,    /* 2: NMI Handler */
    (uint32_t)Default_Handler,    /* 3: Hard Fault Handler */
    (uint32_t)Default_Handler,    /* 4: MPU Fault Handler */
    (uint32_t)Default_Handler,    /* 5: Bus Fault Handler */
    (uint32_t)Default_Handler,    /* 6: Usage Fault Handler */
    0, 0, 0, 0,                   /* 7-10: Reserved */
    (uint32_t)Default_Handler,    /* 11: SVCall Handler */
    (uint32_t)Default_Handler,    /* 12: Debug Monitor Handler */
    0,                            /* 13: Reserved */
    (uint32_t)Default_Handler,    /* 14: PendSV Handler */
    (uint32_t)Default_Handler,    /* 15: SysTick Handler */
};



__attribute__((naked, noreturn)) 
void Reset_Handler(void)
{
    SCB->VTOR = (uint32_t)vectors;

    uint32_t *src = &_etext;
    uint32_t *dst = &_sdata;
    while(dst < &_edata) {
        *dst++ = *src++;
    }

    dst = &_sbss;
    while(dst < &_ebss) {
        *dst++ = 0;
    }

    SystemInit();
    main();

    while(1);
}

void SystemInit(void) {
    WWDT0->MOD = 0; 
    SYSCON->ECC_ENABLE_CTRL = 0;
    LPCAC0->LPCAC_CTRL |= 1UL;

    SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2) | 
                   (3UL << 0*2)  | (3UL << 1*2));

    __DSB();
    __ISB();
}
