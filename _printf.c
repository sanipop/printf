#include <stdio.h>
#include <stdarg.h>
#include "main.h"
/**
 * _printf - Printf function
 * @format: array of characters
 * Return: Always 0
 */
int _printf(const char *format, ...)
{
	
	int lp = 0;
	int i;
	va_list args;
	va_start(args, format);
	if (format == NULL)
	{
		return (-1);
	}
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (!*format) 
			{

        			return -1;
			}
			switch (*format)
			{
				case 'c':
					lp += printf("%c", va_arg(args, int));
					break;
				case 's':
					lp += printf("%s", va_arg(args, char *));
					break;
				case 'd':
				case 'i':
					lp += printf("%d", va_arg(args, int));
					break;
				case 'u':
					lp += printf("%u", va_arg(args, unsigned int));
					break;
				case 'o':
					lp += printf("%o", va_arg(args, unsigned int));
					break;
				case 'x':
					lp += printf("%x", va_arg(args, int));
					break;
				case 'X':
					lp += printf("%X", va_arg(args, int));
					break;
				case 'p':
					lp += printf("%p", va_arg(args, void *));
					break;
				case 'b':
					{
					unsigned int num = va_arg(args, unsigned int);
					char buffer[32];
					int index = 0;
					if (num == 0) {
					return printf("0");
					}
					else 
					{
						while (num > 0)
						{
							buffer[index++] = num % 2;
							num /= 2;
						}
							for (i = index - 1; i >= 0; i--)
							{
								printf("%d", buffer[i]);
							}
					}
						break;
					}
				case '%':
					lp += printf("%%");
					break;
				default:
					lp += printf("%%%c", *format);
					break;
			}
			}
			else 
			{
				lp += printf("%c", *format);
			}
		format++;
	}
	va_end(args);
	return (lp);
}
