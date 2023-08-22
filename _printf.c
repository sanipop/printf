#include <stdio.h>
#include <stdarg.h>
#include "main.h"

/**
 * _print f - the function
 * @format: string of characters that is a constant and also a pointer
 * return: Always 0
 */

int _printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

	int i;
	int count = 0;
	char hold;
	char *str = va_arg(args, char *); 

    for (i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            i++; 
            
            switch (format[i]) {
                case 'c':
                    hold = va_arg(args, int); 
                    putchar(hold);
                    count++;
                    break;

                case 's':
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

int main() {
    int count = _printf("Hello, %s! This is a %c test %%.\n", "world", 'C');
    printf("\nTotal characters printed: %d\n", count);
    return 0;
}
