#include "main.h"
#include "arm_math.h"
#include "ti_msp_dl_config.h"
#include "delay.h"
#include "stdio.h"


 int main(void){

    SYSCFG_DL_init();

    while (1){

        DL_GPIO_togglePins(GPIO_GRP_0_PORT, GPIO_GRP_0_LD0_PIN);
        printf("Hello World\n");

        Delay_tick(500);
    }

}
