#include "fsl_device_registers.h"

int main(void) {
    WWDT0->MOD = 0x00; 
  
    PORT0->PCR[10] = 0;
    PORT0->PCR[27] = 0;
    PORT1->PCR[2]  = 0;

    while (1) {
        __asm("nop");
    }
    
    return 0 ;
}
