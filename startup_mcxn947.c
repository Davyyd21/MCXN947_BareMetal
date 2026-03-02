#include "fsl_device_registers.h"
#include <stdint.h>

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _stack_top;
extern uint32_t _vStackBase;

void Reset_Handler(void) __attribute__((naked, noreturn));
void SystemInit(void);
extern int main(void);

void Default_Handler(void) {
    while (1);
}

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
    (uint32_t)&_stack_top,
    (uint32_t)Reset_Handler,
    (uint32_t)NMI_Handler,
    (uint32_t)HardFault_Handler,
    (uint32_t)MemManage_Handler,
    (uint32_t)BusFault_Handler,
    (uint32_t)UsageFault_Handler,
    (uint32_t)SecureFault_Handler,
    0, 0, 0,
    (uint32_t)SVC_Handler,
    (uint32_t)DebugMon_Handler,
    0,
    (uint32_t)PendSV_Handler,
    (uint32_t)SysTick_Handler,
};



__attribute__((naked, noreturn))
void Reset_Handler(void)
{
    __asm volatile ("cpsid i");

    SCB->VTOR = (uint32_t)vectors;
    __asm volatile ("MSR MSPLIM, %0" : : "r"(&_vStackBase));

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

    __asm volatile ("cpsie i");

    main();

    while(1);
}

void SystemInit(void) {
    WWDT0->MOD = 0; 

    SYSCON->ECC_ENABLE_CTRL = 0;
    CACHE64_CTRL0->CCR |= 1UL;

    /* 3. FPU & PowerQuad */
    SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2) | (3UL << 0*2) | (3UL << 1*2));

    __DSB();
    __ISB();
}