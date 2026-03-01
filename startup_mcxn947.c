#include "fsl_device_registers.h"
#include <stdint.h>

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _stack_top;

void Reset_Handler(void);
void SystemInit(void);
extern int main(void);

void Default_Handler(void) { while (1); }

void NMI_Handler(void)          __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler(void)    __attribute__ ((weak, alias("Default_Handler")));
void MemManage_Handler(void)    __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler(void)     __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler(void)   __attribute__ ((weak, alias("Default_Handler")));
void SecureFault_Handler(void)  __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler(void)          __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler(void)     __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler(void)      __attribute__ ((weak, alias("Default_Handler")));

__attribute__((section(".isr_vector"), used))
const uint32_t vectors[] = {
    (uint32_t)&_stack_top,        /* 0: Initial Stack Pointer */
    (uint32_t)Reset_Handler,      /* 1: Reset Handler */
    (uint32_t)NMI_Handler,        /* 2: NMI Handler */
    (uint32_t)HardFault_Handler,  /* 3: Hard Fault Handler */
    (uint32_t)MemManage_Handler,  /* 4: MPU Fault Handler */
    (uint32_t)BusFault_Handler,   /* 5: Bus Fault Handler */
    (uint32_t)UsageFault_Handler, /* 6: Usage Fault Handler */
    (uint32_t)SecureFault_Handler,/* 7: Secure Fault Handler */
    0, 0, 0,                      /* 8-10: Reserved */
    (uint32_t)SVC_Handler,        /* 11: SVCall Handler */
    (uint32_t)DebugMon_Handler,   /* 12: Debug Monitor Handler */
    0,                            /* 13: Reserved */
    (uint32_t)PendSV_Handler,     /* 14: PendSV Handler */
    (uint32_t)SysTick_Handler,    /* 15: SysTick Handler */
};

__attribute__((noreturn))
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
    CACHE64_CTRL0->CCR |= 1UL;

    // Enable FPU
    SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2) | (3UL << 0*2) | (3UL << 1*2));

    __DSB();
    __ISB();
}
