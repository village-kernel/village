//###########################################################################
// stdint.h
// Header file for stdint classes
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __STDINT_H__
#define __STDINT_H__

#if defined(ARCH_X86)

#define int8_t          char
#define int16_t         short
#define int32_t         long
#define int64_t         long int

#define uint8_t         unsigned char
#define uint16_t        unsigned short
#define uint32_t        unsigned long
#define uint64_t        unsigned long int

#elif defined(ARCH_ARM)

#define int8_t          char
#define int16_t         short
#define int32_t         int
#define int64_t         long

#define uint8_t         unsigned char
#define uint16_t        unsigned short
#define uint32_t        unsigned int
#define uint64_t        unsigned long

#endif

#define __ASM(code)     asm volatile(code)

#endif // !__STDINT_H__
