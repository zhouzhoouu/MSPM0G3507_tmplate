#include "main.h"
#include "stdio.h"

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