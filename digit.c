#include "main.h"

/**
 * p_num - prints chars and base-10 integers
 * @list: arguments list
 * @b: format specifications
 * Return: formatted str
 */
char *p_num(va_list list, str_list *b)
{
	unsigned long int n = va_arg(list, unsigned long int);

	if (_strchr("uid", b->type))
		return (p_base10(n, b));

	return (p_base2(n, b));
}

/**
 * p_c - print char
 * @c: char
 * @i_enjoy_this: yay
 * Return: char string
 **/
char *p_c(int c, int *i_enjoy_this)
{
	static int null_byte;
	char *str;

	if (i_enjoy_this)
	{
		*i_enjoy_this += null_byte;
		return (NULL);
	}

	if (c == '\0')
		null_byte++;

	str = malloc(2);
	if (str == NULL)
		return (NULL);
	*str = c;
	*(str + 1) = '\0';

	return (str);
}

/**
 * p_base10 - returns a decimal string representation of a number
 * @n: num to turn to str
 * @f: format specifications
 * Return: pointer to decimal string representation of n
 **/
char *p_base10(unsigned long int n, str_list *f)
{
	unsigned long int size = 1E19, print = 0, max;
	char *buf = malloc(21), *tmp = buf;

	if (buf == NULL)
		return (NULL);

	if (f->len == 'l')
		max = LONG_MAX;
	if (f->len == 'h')
		max = SHRT_MAX;
	else
		max = INT_MAX;

	if (f->type != 'u')
	{
		if (n > max)
		{
			*buf++ = '-';
			n = ~(n - 1) & (max < UINT_MAX ? UINT_MAX : ULONG_MAX);
		}
		else if (f->plus)
			*buf++ = '+';
		else if (f->space)
			*buf++ = ' ';
	}
	for (; size; size /= 10)
		if ((n / size) || print || size == 1)
		{
			print = 1;
			*buf++ = (n / size) + '0';
			n %= size;
		}
	*buf = '\0';
	return (tmp);
}

/**
 * p_base2 - prints numbers, addresses, and single chars
 * @n: number to print
 * @f: format specifications
 * Return: formatted str
 */
char *p_base2(unsigned long int n, str_list *f)
{
	unsigned long int i, check, power = 4, hex_shift = 0, bits = 32, print = 0;
	char *buf = malloc(65), *p = buf;

	if (buf == NULL)
		return (NULL);
	if (f->len == 'l' || f->type == 'p')
		bits = 64;
	if (f->type == 'b')
		power = 1;
	else if (f->type == 'o')
		power = 3;
	if (f->type == 'x' || f->type == 'p')
		hex_shift = 39;
	else if (f->type == 'X')
		hex_shift = 7;
	if ((f->hash && f->type != 'b') || f->type == 'p')
	{
		*p++ = '0';
		if (f->type == 'x' || f->type == 'p')
			*p++ = 'x';
		else if (f->type == 'X')
			*p++ = 'X';
	}
	while (bits)
	{
		for (i = 0, check = 1; check; check = bits % power)
			i = (i << 1) + ((n >> --bits) & 1);
		if (i > 9)
			i += hex_shift;
		if (!print)
			print = (i & 15);
		if (print)
			*p++ = i + '0';
	}
	if (n == 0)
		*p++ = '0';
	*p = '\0';
	return (buf);
}

