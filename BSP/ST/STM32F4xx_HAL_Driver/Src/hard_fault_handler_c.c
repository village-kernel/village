//###########################################################################
// hard_fault_handler.c
// C handler used for debugging hard faults, should be called by assembly
//
// courtesy of:
// https://blog.frankvh.com/2011/12/07/cortex-m3-m4-hard-fault-handler/
//
// $Copyright: Copyright (C) village
//###########################################################################

#include "stm32f4xx.h"

void HardFault_Handler(void)
{
	__ASM("TST LR, #4");
	__ASM("ITE EQ");
	__ASM("MRSEQ R0, MSP");
	__ASM("MRSNE R0, PSP");
	__ASM("B hard_fault_handler_c");
}

void hard_fault_handler_c(unsigned int * hardfault_args)
{
	volatile uint32_t stacked_r0;
	volatile uint32_t stacked_r1;
	volatile uint32_t stacked_r2;
	volatile uint32_t stacked_r3;
	volatile uint32_t stacked_r12;
	volatile uint32_t stacked_lr;
	volatile uint32_t stacked_pc;
	volatile uint32_t stacked_psr;

	stacked_r0 = ((uint32_t)hardfault_args[0]);
	stacked_r1 = ((uint32_t)hardfault_args[1]);
	stacked_r2 = ((uint32_t)hardfault_args[2]);
	stacked_r3 = ((uint32_t)hardfault_args[3]);

	stacked_r12 = ((uint32_t)hardfault_args[4]);
	stacked_lr  = ((uint32_t)hardfault_args[5]);
	stacked_pc  = ((uint32_t)hardfault_args[6]);
	stacked_psr = ((uint32_t)hardfault_args[7]);

	while (1);
}