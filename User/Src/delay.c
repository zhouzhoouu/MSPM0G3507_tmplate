#include "delay.h"

volatile uint64_t Tick_Counter = 0;

uint64_t Get_SysTick(void){
    return  Tick_Counter;
}

void Delay_tick(uint32_t t){
    uint64_t t_s = Get_SysTick();
    while (Get_SysTick() - t_s < t){
        __NOP();
    }
}

void SysTick_Handler(void){
    Tick_Counter++;
}