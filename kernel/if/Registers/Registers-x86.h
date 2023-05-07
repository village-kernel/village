//###########################################################################
// Registers-x86.h
// Declarations of the i386 registers
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __REGISTERS_X86_H__
#define __REGISTERS_X86_H__

struct Registers
{
	uint32_t eax;
	uint32_t ecx;
	uint32_t edx;
	uint32_t ebx;
	uint32_t esp;
	uint32_t ebp;
	uint32_t esi;
	uint32_t edi;
	uint32_t eip;
	uint32_t eflags;

	Registers
	(
		uint32_t eip = 0, 
		uint32_t eax = 0,
		uint32_t ecx = 0,
		uint32_t edx = 0,
		uint32_t ebx = 0,
		uint32_t esp = 0,
		uint32_t ebp = 0,
		uint32_t esi = 0,
		uint32_t edi = 0
	):
		eax(eax),
		ecx(ecx),
		edx(edx),
		ebx(ebx),
		esp(esp),
		ebp(ebp),
		esi(esi),
		edi(edi),
		eip(eip),
		eflags(0x00000000u)
	{}
};

#endif //!__REGISTERS_X86_H__
