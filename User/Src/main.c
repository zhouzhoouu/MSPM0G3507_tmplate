#include "main.h"
#include "arm_math.h"
#include "ti_msp_dl_config.h"

#include "stdio.h"


 int main(void){

    SYSCFG_DL_init();

    uint8_t dats[] = "aaa\n";


    while (1){

        DL_GPIO_togglePins(GPIO_GRP_0_PORT, GPIO_GRP_0_LD0_PIN);

        printf("Test:%-5.3f\n",-1.78513f);

        for (volatile uint32_t i = 0; i < 1000000; i++) {
            __NOP();  // 可选，防止优化
        }

    }

}