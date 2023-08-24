#include <stdio.h>
#include <stdarg.h>
#include "main.h"

/**
 * _printf - dupe of printf function
 * @format: char strings
 * Return: 0
 */

int _printf(const char *format, ...)
{

    int i;
    int tf = 0;

    va_list args;

    va_start(args, format);

    if (format == NULL)
    {
        return -1;
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
                    tf += printf("%c", va_arg(args, int));
                    break;

                case 's':
                    tf += printf("%s", va_arg(args, char *));
                    break;

                case 'd':
                case 'i':
                    tf += printf("%d", va_arg(args, int));
                    break;

                case 'u':
                    tf += printf("%u", va_arg(args, unsigned int));
                    break;

                case 'o':
                    tf += printf("%o", va_arg(args, unsigned int));
                    break;

                case 'x':
                    tf += printf("%x", va_arg(args, int));
                    break;

                case 'X':
                    tf += printf("%X", va_arg(args, int));
                    break;

                case 'p':
                    tf += printf("%p", va_arg(args, void *));
                    break;

                case 'b': {
                    unsigned int num = va_arg(args, unsigned int);
                    char buffer[64];
                    int index = 0;

                    if (num == 0) {
                        tf += printf("0");
                    }
                    else {
                        while (num > 0) {
                            buffer[index++] = num % 2;
                            num /= 2;
                        }
                        for (i = index - 1; i >= 0; i--) {
                            tf += printf("%d", buffer[i]);
                        }
                    }
                    break;
                }

                case '%':
                    tf += printf("%%");
                    break;

                default:
                    tf += printf("%%%c", *format);
                    break;
            }
        }
        else {
            tf += printf("%c", *format);
        }

        format++;
    }

    va_end(args);
    return tf;
}
