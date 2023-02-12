//###########################################################################
// hard_fault_handler.c
// C handler used for debugging hard faults, should be called by assembly
//
// courtesy of:
// https://blog.frankvh.com/2011/12/07/cortex-m3-m4-hard-fault-handler/
//
// $Copyright: Copyright (C) jingwei
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
	volatile unsigned int stacked_r0;
	volatile unsigned int stacked_r1;
	volatile unsigned int stacked_r2;
	volatile unsigned int stacked_r3;
	volatile unsigned int stacked_r12;
	volatile unsigned int stacked_lr;
	volatile unsigned int stacked_pc;
	volatile unsigned int stacked_psr;

	stacked_r0 = ((unsigned long)hardfault_args[0]);
	stacked_r1 = ((unsigned long)hardfault_args[1]);
	stacked_r2 = ((unsigned long)hardfault_args[2]);
	stacked_r3 = ((unsigned long)hardfault_args[3]);

	stacked_r12 = ((unsigned long)hardfault_args[4]);
	stacked_lr = ((unsigned long)hardfault_args[5]);
	stacked_pc = ((unsigned long)hardfault_args[6]);
	stacked_psr = ((unsigned long)hardfault_args[7]);

	while (1);
}