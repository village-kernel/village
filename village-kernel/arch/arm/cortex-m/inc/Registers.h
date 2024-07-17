//###########################################################################
// Registers-ARM.h
// Declarations of the arm registers
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __REGISTERS_ARM_H__
#define __REGISTERS_ARM_H__

#include "stdint.h"

struct Registers
{
	uint32_t r4;
	uint32_t r5;
	uint32_t r6;
	uint32_t r7;
	uint32_t r8;
	uint32_t r9;
	uint32_t r10;
	uint32_t r11;

	uint32_t irq;
	uint32_t ilr;

	uint32_t r0;
	uint32_t r1;
	uint32_t r2;
	uint32_t r3;
	uint32_t r12;
	uint32_t lr;
	uint32_t pc;
	uint32_t xpsr;

	Registers
	(
		uint32_t pc = 0, 
		uint32_t r0 = 0,
		uint32_t r1 = 0,
		uint32_t r2 = 0,
		uint32_t r3 = 0,
		uint32_t r4 = 0,
		uint32_t r5 = 0,
		uint32_t r6 = 0,
		uint32_t r7 = 0,
		uint32_t r8 = 0,
		uint32_t r9 = 0,
		uint32_t r10 = 0,
		uint32_t r11 = 0,
		uint32_t r12 = 0
	):
		r4(r4),
		r5(r5),
		r6(r6),
		r7(r7),
		r8(r8),
		r9(r9),
		r10(r10),
		r11(r11),
		irq(0),
		ilr(0),
		r0(r0),
		r1(r1),
		r2(r2),
		r3(r3),
		r12(r12),
		lr(0xFFFFFFFDu),
		pc(pc),
		xpsr(0x01000000u)
	{}
} __attribute__((packed));

struct TaskContext
{
	uint32_t r4;
	uint32_t r5;
	uint32_t r6;
	uint32_t r7;
	uint32_t r8;
	uint32_t r9;
	uint32_t r10;
	uint32_t r11;

	uint32_t ilr;

	uint32_t r0;
	uint32_t r1;
	uint32_t r2;
	uint32_t r3;
	uint32_t r12;
	uint32_t lr;
	uint32_t pc;
	uint32_t xpsr;

	TaskContext
	(
		uint32_t pc = 0, 
		uint32_t r0 = 0,
		uint32_t r1 = 0,
		uint32_t r2 = 0,
		uint32_t r3 = 0
	):
		r4(0),
		r5(0),
		r6(0),
		r7(0),
		r8(0),
		r9(0),
		r10(0),
		r11(0),
		ilr(0xFFFFFFE9u),
		r0(r0),
		r1(r1),
		r2(r2),
		r3(r3),
		r12(0),
		lr(0xFFFFFFE9u),
		pc(pc),
		xpsr(0x01000000u)
	{}
} __attribute__((packed));

#endif //!__REGISTERS_ARM_H__
