#ifndef MAIN_H
#define MAIN_H

/* HEADER FILES */
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

/*CONSTANT*/
#define AMS_F_ZERO   1
#define AMS_F_MINUS  2
#define AMS_F_PLUS   4
#define AMS_F_SPACE  8
#define AMS_S_LONG   1
#define AMS_S_SHORT  2
#define AMS_BUFF_SIZE 1024
#define UNUSED(x) (void)(x)

/* PRE-PROCESSOR DIRECTIVES */
#define is_alpha(a) ((a >= 'A' && a <= 'Z') || (a >= 'a' && a <= 'z'))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define is_digit(a) ((a) >= '0' && (a) <= '9')
#define add_times_user_tried_printing_a_null_byte(a) p_c(0, &a)
#define true 1
#define false 0

/* STRUCTS */

/**
 * struct str_list_s - node of list of strings and their format specifications
 * @str:		string
 * @type:		string type (e.g. s in '%s', c in '%c')
 * @len:		if 1, print long int. if -1, print short int.
 * @minus:		if 1, print right-aligned
 * @plus:		if 1, print the '+' sign before an integer
 * @space:		if 1, print placeholder chars with spaces
 * @zero:		if 1, print placeholder chars with zeroes
 * @hash:		if 1, print non-base 10 digits with prefixes
 * @has_min:	has a width value
 * @width:		minimum number of chars to print
 * @has_max:	has a precision value
 * @precision:	maximum number of chars to print
 * @next:		pointer to next str_list node
 **/
typedef struct str_list_s
{
	char *str;
	int type;
	int len;
	int minus;
	int plus;
	int space;
	int zero;
	int hash;
	int has_min;
	int width;
	int has_max;
	int precision;
	struct str_list_s *next;
} str_list;

/**
 * struct p_dict_s - matches a format specifier with a printer
 * @type:	allowable format specifiers for...
 * @printer:		...this specific printer
 **/
typedef struct p_dict_s
{
	char *type;
	char *(*printer)(va_list, str_list *);
} print_dict;

int _printf(const char *format, ...);
int build_str_list(str_list **, va_list, const char *);
int add_str(str_list **, const char **, const char *, va_list);
char *get_string(str_list *, const char *, va_list);
char *strncopy_list(str_list *, int);

char *p_num(va_list, str_list *);
char *p_c(int, int *);
char *p_base2(unsigned long int, str_list *);
char *p_base10(unsigned long int, str_list *);

char *p_s(va_list, str_list *);
char *rev_string(char *);
char *rot13(char *);
char *p_S(char *);
char *p_mod(va_list, str_list *);

char *_strchr(char *, char);
char *_strdup(char *);
size_t _strlen(char *);
void free_strlist(str_list *);
str_list *new_str_list_node(void);

/*FOR TASK1*/
long int convert_s_n(long int num, int size);
int write_n0(int ind, char buffer[],
              int flags, int width, int prec,
              int length, char padd, char extra_c);
int write_n1(int is_negative, int ind, char buffer[],
                 int flags, int width, int precision, int size);
int p_i(va_list types, char buffer[],
              int flags, int width, int precision, int size);

#endif /* MAIN_H */
