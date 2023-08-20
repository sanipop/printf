#include <stdio.h>
#include <stdarg.h>
#include "main.h"

int _printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    int count = 0;  // track the characters printed
    char ch;        // To store individual characters from format

    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            i++; 
            
            switch (format[i]) {
                case 'c':
                    ch = va_arg(args, int); 
                    putchar(ch);
                    count++;
                    break;

                case 's':
                    char *str = va_arg(args, char *); 
                    while (*str != '\0') {
                        putchar(*str);
                        str++;
                        count++;
                    }
                    break;

                case '%':
                    putchar('%');
                    count++;
                    break;

                default:
                    putchar('%');
                    putchar(format[i]);
                    count += 2;
            }
        } else {
            putchar(format[i]); 
            count++;
        }
    }

    va_end(args);  
    return count;
}
