#include "main.h"

int _printf(const char *format, ...)
{
    va_list item;
    int len;
    char *output;
    str_list *h = NULL;

    if (format == NULL)
        return -1;

    va_start(item, format);

    len = build_str_list(&h, item, format);
    if (len == -1)
        return -1;

    output = strncopy_list(h, len);
    len = write(1, output, len);

    va_end(item);
    free(output);
    free_strlist(h);

    add_times_user_tried_printing_a_null_byte(len);

    return len;
}

int build_str_list(str_list **h, va_list item, const char *str)
{
    int len = 0, new_str_len;
    const char *tmp = str;

    if (str == NULL)
        return -1;

    while (*str)
    {
        if (*str++ != '%')
            continue;
        if (*str == '\0')
            return -1;
        new_str_len = add_str(h, &str, tmp, item);
        if (new_str_len == -1)
            return -1;
        len += new_str_len;
        tmp = ++str;
    }
    new_str_len = add_str(h, &str, tmp, item);
    if (new_str_len == -1)
        return -1;
    len += new_str_len;
    return len;
}

int add_str(str_list **h, const char **in, const char *alt, va_list item)
{
    str_list *tmp = *h, *b = new_str_list_node();

    if (b == NULL)
        return -1;
    if (*h)
    {
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = b;
    }
    else
        *h = b;

    for (; **in; (*in)++)
    {
        if (**in == '-' || **in == '+' || **in == ' ' || **in == '0' || **in == '#')
        {
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
        }
        else
        {
            break;
        }
    }

    if (is_digit(**in))
    {
        for (b->has_min = true; is_digit(**in); (*in)++)
        {
            b->width = (b->width * 10) + (**in - '0');
        }
    }
    if (**in == '.')
    {
        for (b->has_max = true, (*in)++; is_digit(**in); (*in)++)
        {
            b->precision = (b->precision * 10) + (**in - '0');
        }
    }
    if (**in == 'l' || **in == 'h')
    {
        b->len = *(*in)++;
    }
    b->type = **in;
    b->str = get_string(b, alt, item);
    if (b->str == NULL)
        return -1;
    return _strlen(b->str);
}

char *fetch_string(str_list *b, const char *alt, va_list item)
{
    print_dict pd[] = {{"bdiopuxX", p_num}, {"csrRS", p_s}, {"%", p_mod}};
    int i, j, len, arg_len, total_len;
    char *arg = NULL, *tmp = NULL;

    for (i = 0; i < 3; i++)
    {
        if (_strchr(pd[i].type, b->type))
        {
            tmp = pd[i].printer(item, b);
            if (tmp == NULL)
                return NULL;
            break;
        }
    }

    for (i = 0; alt[i] && alt[i] != '%'; i++)
        ;

    arg_len = i;
    if (tmp == NULL && alt[i])
    {
        for (arg_len++; alt[i] != b->type; i++)
            arg_len++;
    }

    len = _strlen(tmp);
    total_len = len + arg_len;
    arg = malloc(total_len + 1);

    if (arg == NULL)
        return NULL;

    for (i = 0; i < arg_len; i++)
        arg[i] = alt[i];

    for (j = 0; i < total_len; i++, j++)
        arg[i] = tmp[j];

    arg[i] = '\0';
    free(tmp);
    return arg;
}

char *strncopy_list(str_list *h, int n)
{
    int len, width, print_spaces, i, j, k;
    char *buf = malloc(n + 1), space = ' ';

    if (buf == NULL)
        return NULL;

    for (i = 0; h; h = h->next)
    {
        len = _strlen(h->str);
        print_spaces = ~(h->minus);

        if (h->has_max)
            len = min(h->precision, len);

        if (h->has_min)
            width = max(h->width, len);
        else
            width = len;

        if (h->zero && _strchr("bcdiopuxX", h->type))
            space = '0';

        for (k = i; i - k < width; print_spaces = true)
        {
            if (print_spaces == true)
            {
                for (j = i + width - len; i < j; i++, j++)
                {
                    buf[i] = space;
                }
            }

            for (j = 0; i - k < len; i++, j++)
            {
                buf[i] = h->str[j];
            }
        }
    }

    buf[i] = '\0';
    return buf;
}

