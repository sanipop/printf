#include <stdio.h>
#include <stdarg.h>
#include "main.h"

int _printf(const char *format, ...)
{
	va_list items;
	int len;
	char *output;
	str_list *h = NULL;

	if (format == NULL)
		return (-1);

	va_start(items, format);

	len = build_str_list(&h, items, format);
	if (len == -1)
		return (-1);

	output = strncopy_list(h, len);
	len = write(1, output, len);

	va_end(items);
	free(output);
	free_strlist(h);

	add_times_user_tried_printing_a_null_byte(len);

	return (len);
}

/**
 * @h: str_list head
 * @items: argument list
 * @str: string
 * Return: number of characters
 **/
int create_str_list(str_list **h, va_list items, const char *str)
{
	int len = 0, new_str_len;
	const char *tmp = str;

	if (str == NULL)
		return (-1);

	while (*str)
	{
		if (*str++ != '%')
			continue;
		if (*str == '\0')
			return (-1);
		new_str_len = add_str(h, &str, tmp, items);
		if (new_str_len == -1)
			return (-1);
		len += new_str_len;
		tmp = ++str;
	}
	new_str_len = add_str(h, &str, tmp, items);
	if (new_str_len == -1)
		return (-1);
	len += new_str_len;
	return (len);
}

/**
 * @h: pointer to str list
 * @in: pointer to input string
 * @alte: alternative string to add items if arg string is not available
 * @items: arg list containing arg str
 **/
int add_str(str_list **h, const char **in, const char *alte, va_list items)
{
	str_list *tmp = *h, *b = new_str_list_node();

	if (b == NULL)
		return (-1);
	if (*h)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = b;
	}
	else
		*h = b;

	for (; **in; (*in)++)
		if (**in == '-')
			b->minus = true;
		else if (**in == '+')
			b->plus = true;
		else if (**in == ' ')
			b->space = true;
		else if (**in == '0')
			b->zero = true;
		else if (**in == '#')
			b->hash = true;
		else
			break;

	if (is_digit(**in))
		for (b->has_min = true; is_digit(**in); (*in)++)
			b->width = (b->width * 10) + (**in - '0');
	if (**in == '.')
		for (b->has_max = true, (*in)++; is_digit(**in); (*in)++)
			b->precision = (b->precision * 10) + (**in - '0');
	if (**in == 'l' || **in == 'h')
		b->len = *(*in)++;
	b->type = **in;
	b->str = get_string(b, alte, items);
	if (b->str == NULL)
		return (-1);
	return (_strlen(b->str));
}
