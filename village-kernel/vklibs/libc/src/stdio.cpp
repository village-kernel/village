//###########################################################################
// stdio.cpp
// Source file for stdio classes
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "stdio.h"
#include "ctype.h"
#include "string.h"
#include <stdarg.h>
#include <stdlib.h>


#define ZEROPAD  1  // Pad with zeros (e.g., "0012" instead of "  12")
#define SIGN     2  // Signed number (handles negative values)
#define PLUS     4  // Always show '+' for positive numbers (e.g., "+42")
#define SPACE    8  // Add a space for non-negative numbers (e.g., " 42")
#define LEFT    16  // Left-justify the output (e.g., "42  " instead of "  42")
#define SMALL   32  // Use lowercase hex digits (e.g., "0x1a" instead of "0x1A")
#define SPECIAL 64  // Add prefixes (e.g., "0x" for hex or "0" for octal)


/// @brief putchar
/// @param c 
/// @return 
extern "C" __attribute__((weak)) int putchar(int c)
{
    return 0;
}


/// @brief puts
/// @param str 
/// @return 
extern "C" __attribute__((weak)) int puts(const char* str)
{
    while (*str)
    {
        putchar(*str++);
    }
    putchar('\n');
    return 0;
}


/// @brief printf
/// @param format  Format string
/// @param ...     Variable arguments
/// @return Number of characters written
extern "C" int printf(const char* format, ...)
{
    va_list ap;
    char buf[512];
    int len;

    va_start(ap, format);
    len = vsnprintf(buf, sizeof(buf), format, ap);
    va_end(ap);

    puts(buf);
    return len;
}


/// @brief sprintf
/// @param str     Output buffer
/// @param format  Format string
/// @param ...     Variable arguments
/// @return Number of characters written
extern "C" int sprintf(char* str, const char* format, ...)
{
    va_list ap;
    int len;

    va_start(ap, format);
    len = vsnprintf(str, 512, format, ap);
    va_end(ap);

    return len;
}


/// @brief snprintf
/// @param str     Output buffer
/// @param size    Buffer size
/// @param format  Format string
/// @param ...     Variable arguments
/// @return Number of characters written
extern "C" int snprintf(char* str, size_t size, const char* format, ...)
{
    va_list ap;
    int len;

    va_start(ap, format);
    len = vsnprintf(str, size, format, ap);
    va_end(ap);

    return len;
}


/// @brief asprintf
/// @param ret     Pointer to the allocated buffer
/// @param format  Format string
/// @param ...     Variable arguments
/// @return Number of characters written (excluding null terminator)
extern "C" int asprintf(char** ret, const char* format, ...)
{
    va_list ap;
    va_start(ap, format);
    int len = vsnprintf(NULL, 0, format, ap);
    va_end(ap);

    if (len < 0)
    {
        return -1;
    }

    *ret = (char*)malloc(len + 1);
    if (!*ret)
    {
        return -1;
    }

    va_start(ap, format);
    len = vsnprintf(*ret, len + 1, format, ap);
    va_end(ap);

    return len;
}


/// @brief dprintf
/// @param fd      File descriptor
/// @param format  Format string
/// @param ...     Variable arguments
/// @return Number of characters written
extern "C" int dprintf(int fd, const char* format, ...)
{
    va_list ap;
    char buf[512];
    int len;

    va_start(ap, format);
    len = vsnprintf(buf, sizeof(buf), format, ap);
    va_end(ap);

    // write(fd, buf, len);
    return len;
}


/// @brief vprintf
/// @param format Format string
/// @param ap Argument list
/// @return Number of characters written
extern "C" int vprintf(const char* format, va_list ap)
{
    char buf[512];
    int len = vsprintf(buf, format, ap);
    puts(buf);
    return len;
}


/// @brief vsprintf
/// @param buf Output buffer
/// @param format Format string
/// @param ap Argument list
/// @return Number of characters written
extern "C" int vsprintf(char* buf, const char* format, va_list ap)
{
    return vsnprintf(buf, 512, format, ap);
}


/// @brief Helper function to format a number into a string
/// @param str   Output buffer
/// @param num   Number to format
/// @param base  Base (e.g., 10 for decimal, 16 for hexadecimal)
/// @param size  Field width
/// @param precision Minimum number of digits
/// @param flags Formatting flags (as bitmask)
/// @return Pointer to the end of the formatted string
static char* format_number(char* str, long num, int base, int size, int precision, int flags)
{
    static const char digits[] = "0123456789ABCDEF";       // Uppercase digits for hex
    static const char lower_digits[] = "0123456789abcdef"; // Lowercase digits for hex

    char tmp[66]; // Temporary buffer to store the reversed number string
    char* ptr = tmp;
    
    // Determine whether to use lowercase letters for hex
    const char* digit_set = (flags & SMALL) ? lower_digits : digits;
    
    int sign = 0; // Flag to indicate if the number is negative

    // Handle negative numbers
    if ((flags & SIGN) && num < 0)
    {
        sign = 1; // Set sign flag
        num = -num; // Convert to positive
    }

    // Convert the number to a string (in reverse order)
    do
    {
        *ptr++ = digit_set[num % base]; // Store the digit
        num /= base; // Move to the next digit
    }
    while (num > 0);

    // Add leading zeros for precision
    while (ptr - tmp < precision)
    {
        *ptr++ = '0';
    }

    // Add the sign character if necessary
    if (sign)
    {
        *ptr++ = '-';
    }

    // Reverse the string to get the correct order
    while (ptr > tmp)
    {
        *str++ = *--ptr;
    }

    return str; // Return the pointer to the end of the formatted string
}


/// @brief vsnprintf
/// @param buf   Output buffer
/// @param size  Buffer size
/// @param format Format string
/// @param ap    Argument list
/// @return Number of characters written
extern "C" int vsnprintf(char* buf, size_t size, const char* format, va_list ap)
{
    char* str = buf;
    const char* s;
    int len, i, base, field_width, precision, qualifier;
    int flags = 0;

    for (; *format && (str - buf) < (int)size; ++format)
    {
        if (*format != '%')
        {
            *str++ = *format;
            continue;
        }

        // Parse flags
        flags = 0;
    repeat:
        switch (*++format)
        {
            case '-':
                flags |= LEFT;
                goto repeat;
            case '+':
                flags |= PLUS;
                goto repeat;
            case ' ':
                flags |= SPACE;
                goto repeat;
            case '#':
                flags |= SPECIAL;
                goto repeat;
            case '0':
                flags |= ZEROPAD;
                goto repeat;
        }

        // Parse field width
        field_width = -1;
        if (isdigit(*format))
        {
            field_width = 0;
            while (isdigit(*format))
            {
                field_width = field_width * 10 + (*format++ - '0');
            }
        }
        else if (*format == '*')
        {
            field_width = va_arg(ap, int);
            if (field_width < 0)
            {
                field_width = -field_width;
                flags |= LEFT;
            }
            ++format;
        }

        // Parse precision
        precision = -1;
        if (*format == '.')
        {
            ++format;
            if (isdigit(*format))
            {
                precision = 0;
                while (isdigit(*format))
                {
                    precision = precision * 10 + (*format++ - '0');
                }
            }
            else if (*format == '*')
            {
                precision = va_arg(ap, int);
                ++format;
            }
            if (precision < 0)
            {
                precision = 0;
            }
        }

        // Parse qualifier
        qualifier = -1;
        if (*format == 'h' || *format == 'l' || *format == 'L')
        {
            qualifier = *format++;
        }

        // Default base
        base = 10;

        switch (*format)
        {
            case 'c':
                if (!(flags & LEFT))
                {
                    while (--field_width > 0)
                    {
                        *str++ = ' ';
                    }
                }
                *str++ = (unsigned char)va_arg(ap, int);
                while (--field_width > 0)
                {
                    *str++ = ' ';
                }
                continue;

            case 's':
                s = va_arg(ap, char*);
                len = strnlen(s, precision);
                if (!(flags & LEFT))
                {
                    while (len < field_width--)
                    {
                        *str++ = ' ';
                    }
                }
                for (i = 0; i < len; ++i)
                {
                    *str++ = *s++;
                }
                while (len < field_width--)
                {
                    *str++ = ' ';
                }
                continue;

            case 'p':
                flags |= SMALL;
                base = 16;
                field_width = 2 * sizeof(void*);
                str = format_number(str, (unsigned long)va_arg(ap, void*), base, field_width, precision, flags);
                continue;

            case '%':
                *str++ = '%';
                continue;

            case 'o':
                base = 8;
                break;

            case 'x':
                flags |= SMALL;
            case 'X':
                base = 16;
                break;

            case 'd':
            case 'i':
                flags |= SIGN;
            case 'u':
                break;

            default:
                *str++ = '%';
                if (*format)
                {
                    *str++ = *format;
                }
                continue;
        }

        // Format number
        long num = (qualifier == 'l') ? va_arg(ap, long) : va_arg(ap, int);
        str = format_number(str, num, base, field_width, precision, flags);
    }

    // Null-terminate the string
    if (str - buf < (int)size)
    {
        *str = '\0';
    }
    else
    {
        buf[size - 1] = '\0';
    }

    return str - buf;
}


/// @brief vasprintf
/// @param ret     Pointer to the allocated buffer
/// @param format  Format string
/// @param ap      Argument list
/// @return Number of characters written (excluding null terminator)
extern "C" int vasprintf(char** ret, const char* format, va_list ap)
{
    int len = vsnprintf(NULL, 0, format, ap);
    if (len < 0)
    {
        return -1;
    }

    *ret = (char*)malloc(len + 1);
    if (!*ret)
    {
        return -1;
    }

    return vsnprintf(*ret, len + 1, format, ap);
}


/// @brief vdprintf
/// @param fd      File descriptor
/// @param format  Format string
/// @param ap      Argument list
/// @return Number of characters written
extern "C" int vdprintf(int fd, const char* format, va_list ap)
{
    char buf[512];
    int len = vsnprintf(buf, sizeof(buf), format, ap);

    // write(fd, buf, len);
    return len;
}
