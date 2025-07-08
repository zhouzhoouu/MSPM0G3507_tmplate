#ifndef MSPM0G3507_BASIC_H
#define MSPM0G3507_BASIC_H

#include "main.h"
#include "stdio.h"

uint64_t Get_SysTick(void);
void Delay_tick(uint32_t t);
void uart_send(void* ptr, uint32_t len);
void vofa_send(float* ptr, uint32_t len);

#endif
