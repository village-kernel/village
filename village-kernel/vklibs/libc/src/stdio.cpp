//###########################################################################
// stdio.cpp
// Source file for stdio classes
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "stdio.h"
#include "ctype.h"
#include "string.h"


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
	return 0;
}


/// @brief printf
/// @param  
/// @param  
/// @return 
extern "C" int printf(char const* format, ...)
{
	va_list ap;
	char buf[512];
	int n;

	va_start(ap, format);
	n = vsnprintf(buf, 512, format, ap);
	va_end(ap);

	puts(buf);

	return n;
}


/// @brief sprintf
/// @param str 
/// @param format 
/// @param  
/// @return 
extern "C" int sprintf(char* str, const char* format, ...)
{
	va_list ap;
	int n;

	va_start(ap, format);
	n = vsprintf(str, format, ap);
	va_end(ap);
	return n;
}


/// @brief snprintf
/// @param str 
/// @param size 
/// @param format 
/// @param  
/// @return 
extern "C" int snprintf(char* str, size_t size, const char* format, ...)
{
	va_list ap;
	int n;

	va_start(ap, format);
	n = vsnprintf(str, size, format, ap);
	va_end(ap);
	return n;
}



/// @brief asprintf
/// @param ret 
/// @param format 
/// @param  
/// @return 
extern "C" int asprintf(char** ret, const char* format, ...)
{
	return 0;
}


/// @brief dprintf
/// @param fd 
/// @param format 
/// @param  
/// @return 
extern "C" int dprintf(int fd, const char* format, ...)
{
	return 0;
}


/// @brief vprintf
/// @param format 
/// @param ap 
/// @return 
extern "C" int vprintf(const char* format, va_list ap)
{
	char buf[512];
	int n = vsprintf(buf, format, ap);
	puts(buf);
	return n;
}


/// @brief vsprintf
/// @param str 
/// @param format 
/// @param ap 
/// @return 
extern "C" int vsprintf(char* buf, const char* format, va_list ap)
{
	return vsnprintf(buf, 512, format, ap);
}



/// @brief skip_atoi
/// @param s 
/// @return 
static int skip_atoi(const char **s)
{
	int i = 0;

	while (isdigit(**s))
		i = i * 10 + *((*s)++) - '0';
	return i;
}


/// @brief do_div
/// @param num 
/// @param base 
/// @return 
static int __do_div(long &num, int base)
{
	int res;
	res = ((unsigned long) num) % (unsigned) base;
	num = ((unsigned long) num) / (unsigned) base;
	return res;
}


#define ZEROPAD	1		/* pad with zero */
#define SIGN	2		/* unsigned/signed long */
#define PLUS	4		/* show plus */
#define SPACE	8		/* space if plus */
#define LEFT	16		/* left justified */
#define SMALL	32		/* Must be 32 == 0x20 */
#define SPECIAL	64		/* 0x */


static char *number(char *str, long num, int base, int size, int precision, int type)
{
	/* we are called with base 8, 10 or 16, only, thus don't need "G..."  */
	static const char digits[16] =  {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'}; 

	char tmp[66];
	char c, sign, locase;
	int i;

	/* locase = 0 or 0x20. ORing digits or letters with 'locase'
	 * produces same digits or (maybe lowercased) letters */
	locase = (type & SMALL);
	if (type & LEFT)
		type &= ~ZEROPAD;
	if (base < 2 || base > 16)
		return NULL;
	c = (type & ZEROPAD) ? '0' : ' ';
	sign = 0;
	if (type & SIGN)
	{
		if (num < 0)
		{
			sign = '-';
			num = -num;
			size--;
		}
		else if (type & PLUS)
		{
			sign = '+';
			size--;
		}
		else if (type & SPACE)
		{
			sign = ' ';
			size--;
		}
	}
	if (type & SPECIAL)
	{
		if (base == 16)
			size -= 2;
		else if (base == 8)
			size--;
	}
	i = 0;
	if (num == 0)
		tmp[i++] = '0';
	else
		while (num != 0)
			tmp[i++] = (digits[__do_div(num, base)] | locase);
	if (i > precision)
		precision = i;
	size -= precision;
	if (!(type & (ZEROPAD + LEFT)))
		while (size-- > 0)
			*str++ = ' ';
	if (sign)
		*str++ = sign;
	if (type & SPECIAL)
	{
		if (base == 8)
			*str++ = '0';
		else if (base == 16) {
			*str++ = '0';
			*str++ = ('X' | locase);
		}
	}
	if (!(type & LEFT))
		while (size-- > 0)
			*str++ = c;
	while (i < precision--)
		*str++ = '0';
	while (i-- > 0)
		*str++ = tmp[i];
	while (size-- > 0)
		*str++ = ' ';
	return str;
}


/// @brief vsnprintf
/// @param buf 
/// @param size 
/// @param format 
/// @param ap 
/// @return 
extern "C" int vsnprintf(char* buf, size_t size, const char* format, va_list ap)
{
	int len;
	unsigned long num;
	int i, base;
	char *str;
	const char *s;

	int flags;		    /* flags to number() */

	int field_width;	/* width of output field */
	int precision;		/* min. # of digits for integers; max
				           number of chars for from string */
	int qualifier;		/* 'h', 'l', or 'L' for integer fields */

	for (str = buf; *format; ++format)
	{
		if (*format != '%')
		{
			*str++ = *format;
			continue;
		}

		/* process flags */
		flags = 0;
	repeat:
		++format;		/* this also skips first '%' */
		switch (*format)
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

		/* get field width */
		field_width = -1;
		if (isdigit(*format))
			field_width = skip_atoi(&format);
		else if (*format == '*')
		{
			++format;
			/* it's the next argument */
			field_width = va_arg(ap, int);
			if (field_width < 0) {
				field_width = -field_width;
				flags |= LEFT;
			}
		}

		/* get the precision */
		precision = -1;
		if (*format == '.')
		{
			++format;
			if (isdigit(*format))
				precision = skip_atoi(&format);
			else if (*format == '*')
			{
				++format;
				/* it's the next argument */
				precision = va_arg(ap, int);
			}
			if (precision < 0)
				precision = 0;
		}

		/* get the conversion qualifier */
		qualifier = -1;
		if (*format == 'h' || *format == 'l' || *format == 'L')
		{
			qualifier = *format;
			++format;
		}

		/* default base */
		base = 10;

		switch (*format)
		{
		case 'c':
			if (!(flags & LEFT))
				while (--field_width > 0)
					*str++ = ' ';
			*str++ = (unsigned char)va_arg(ap, int);
			while (--field_width > 0)
				*str++ = ' ';
			continue;

		case 's':
			s = va_arg(ap, char *);
			len = strnlen(s, precision);

			if (!(flags & LEFT))
				while (len < field_width--)
					*str++ = ' ';
			for (i = 0; i < len; ++i)
				*str++ = *s++;
			while (len < field_width--)
				*str++ = ' ';
			continue;

		case 'p':
			if (field_width == -1)
			{
				field_width = 2 * sizeof(void *);
				flags |= ZEROPAD;
			}
			str = number(str,
				     (unsigned long)va_arg(ap, void *), 16,
				     field_width, precision, flags);
			continue;

		case 'n':
			if (qualifier == 'l')
			{
				long *ip = va_arg(ap, long *);
				*ip = (str - buf);
			}
			else
			{
				int *ip = va_arg(ap, int *);
				*ip = (str - buf);
			}
			continue;

		case '%':
			*str++ = '%';
			continue;

			/* integer number formats - set up the flags and "break" */
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
				*str++ = *format;
			else
				--format;
			continue;
		}

		if (qualifier == 'l')
		{
			num = va_arg(ap, unsigned long);
		}
		else if (qualifier == 'h')
		{
			num = (unsigned short)va_arg(ap, int);
			if (flags & SIGN)
				num = (short)num;
		}
		else if (flags & SIGN)
		{
			num = va_arg(ap, int);
		}
		else
		{
			num = va_arg(ap, unsigned int);
		}
		str = number(str, num, base, field_width, precision, flags);
	}
	*str = '\0';
	return str - buf;
}


/// @brief vasprintf
/// @param ret 
/// @param format 
/// @param ap 
/// @return 
extern "C" int vasprintf(char** ret, const char* format, va_list ap)
{
	return 0;
}


/// @brief vdprintf
/// @param fd 
/// @param format 
/// @param ap 
/// @return 
extern "C" int vdprintf(int fd, const char* format, va_list ap)
{
	return 0;
}
