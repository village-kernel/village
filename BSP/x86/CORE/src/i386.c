//###########################################################################
// i386.c
// Low level file that manages i386
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "i386.h"


/// @brief Read a byte from the specified port
/// @param port 
/// @return result
uint8_t PortByteIn(uint16_t port)
{
    uint8_t result;
    /* Inline assembler syntax
     * !! Notice how the source and destination registers are switched from NASM !!
     *
     * '"=a" (result)'; set '=' the C variable '(result)' to the value of register e'a'x
     * '"d" (port)': map the C variable '(port)' into e'd'x register
     *
     * Inputs and outputs are separated by colons
     */
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

/// @brief Write a byte to the specified port
/// @param port 
/// @param data 
void PortByteOut(uint16_t port, uint8_t data)
{
    /* Notice how here both registers are mapped to C variables and
     * nothing is returned, thus, no equals '=' in the asm syntax 
     * However we see a comma since there are two variables in the input area
     * and none in the 'return' area
     */
    __asm__ volatile("out %%al, %%dx" : : "a" (data), "d" (port));
}


/// @brief  Read a word from the specified port
/// @param port 
/// @return result
uint16_t PortWordIn(uint16_t port)
{
    uint16_t result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}


/// @brief Write a word to the specified port
/// @param port 
/// @param data 
void PortWordOut(uint16_t port, uint16_t data)
{
    __asm__ volatile("out %%ax, %%dx" : : "a" (data), "d" (port));
}
