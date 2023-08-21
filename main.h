#ifndef MAIN_H
#define MAIN_H

// HEADER FILES
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

// MAIN FUNCTIONS (_printf.c)
int _printf(const char *format, ...);
int build_str_list(str_list **, va_list, const char *);
int add_str(str_list **, const char **, const char *, va_list);
char *get_string(str_list *, const char *, va_list);
char *strncopy_list(str_list *, int);

#endif /* MAIN_H */
