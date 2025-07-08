#include "basic.h"

volatile uint64_t Tick_Counter = 0;
unsigned char vofa_tail[4] = {0x00, 0x00, 0x80, 0x7f};

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

void uart_send(void* ptr, uint32_t len){
    for (int i = 0; i < len; i++) {
        // 你需要替换成自己的串口输出函数，如：
        DL_UART_transmitData(UART0, ((uint8_t*)ptr)[i]);
        while (!DL_UART_isTXFIFOEmpty(UART0));
    }
}

void vofa_send(float* ptr, uint32_t len){
    uart_send(ptr,len*4);
    uart_send(vofa_tail, 4);
}

int _write(int file, char *ptr, int len) {
    for (int i = 0; i < len; i++) {
        // 你需要替换成自己的串口输出函数，如：
        DL_UART_transmitData(UART0, ptr[i]);
        while (!DL_UART_isTXFIFOEmpty(UART0));
    }
    return len;
}

void _exit(int status)
{
    while(1);
}