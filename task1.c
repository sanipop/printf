#include "main.h"

/**
 * p_i - send int to stdout
 * @types: list of data types
 * @buffer: temp storage for characters to be outputted
 * @flags: Check if it contains flags
 * @width: store the width of value.
 * @precision: degree of accuracy
 * @size: the value of size
 * Return: count of characters sent to stdout
 */
int p_i(va_list types, char buffer[],
             int flags, int width, int precision, int size) {
    int i = AMS_BUFF_SIZE - 2;
    int is_negative = 0;
    long int n = va_arg(types, long int);
    unsigned long int num;

    n = convert_s_n(n, size);

    if (n == 0) {
        buffer[i--] = '0';
    }

    buffer[AMS_BUFF_SIZE - 1] = '\0';
    num = (unsigned long int) n;

    if (n < 0) {
        num = (unsigned long int) ((-1) * n);
        is_negative = 1;
    }

    do {
        buffer[i--] = (num % 10) + '0';
        num /= 10;
    } while (num > 0);

    i++;

    return write_n1(is_negative, i, buffer, flags, width, precision, size);
}


/**
 * convert_size_number - fxn to change num type
 * @num: input to be casted.
 * @size: Number indicating the type to be casted.
 *
 * Return: num in new type 
 */
long int convert_s_n(long int num, int size)
{
	if (size == AMS_S_LONG)
		return (num);
	else if (size == AMS_S_SHORT)
		return ((short)num);

	return ((int)num);
}


/**
 * write_n1 - stdout num
 * @is_negative: check if not positive 
 * @ind: data specifier.
 * @buffer: temp storage for characters to be outputted
 * @flags:  Check if it contains flags
 * @width: get width.
 * @precision: degree of accuracy
 * @size: the value of size
 *
 * Return: count of characters send to stdout.
 */

int write_n1(int is_negative, int ind, char buffer[],
                 int flags, int width, int precision, int size) {
    int length = AMS_BUFF_SIZE - ind - 1;
    char padd = ' ', extra_ch = 0;

    UNUSED(size);

    if ((flags & AMS_F_ZERO) && !(flags & AMS_F_MINUS)) {
        padd = '0';
    }
    
    // Modify the logic for determining extra_ch
    if (is_negative) {
        extra_ch = '-';
    } else if (flags & AMS_F_PLUS && padd != '0') {
        extra_ch = '+';
    } else if (flags & AMS_F_SPACE && padd != '0') {
        extra_ch = ' ';
    }

    return write_n0(ind, buffer, flags, width, precision,
                     length, padd, extra_ch);
}


/**
 * write_n0 - Write a number using a buffer
 * @ind: buffer start position
 * @buffer: temp storage for characters to be outputted
 * @flags: Check if it contains flags
 * @width: width
 * @prec: degree of accuracy
 * @length: size of input characters
 * @padd: Pading char
 * @extra_c: Extra char
 *
 * Return: count of characters sent to stdout.
 */
int write_n0(int ind, char buffer[],
              int flags, int width, int prec,
              int length, char padd, char extra_c) {
    int i, padd_start = 1;
    int total_written = 0;

    if (prec == 0 && ind == AMS_BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
        return 0;
    if (prec == 0 && ind == AMS_BUFF_SIZE - 2 && buffer[ind] == '0')
        buffer[ind] = padd = ' ';
    if (prec > 0 && prec < length)
        padd = ' ';
    while (prec > length)
        buffer[--ind] = '0', length++;
    if (extra_c != 0)
        length++;
    if (width > length) {
        for (i = 1; i < width - length + 1; i++)
            buffer[i] = padd;
        buffer[i] = '\0';
        if (flags & AMS_F_MINUS && padd == ' ') {
            if (extra_c)
                buffer[--ind] = extra_c;
            total_written = write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1);
        } else if (!(flags & AMS_F_MINUS) && padd == ' ') {
            if (extra_c)
                buffer[--ind] = extra_c;
            total_written = write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length);
        } else if (!(flags & AMS_F_MINUS) && padd == '0') {
            if (extra_c)
                buffer[--padd_start] = extra_c;
            total_written = write(1, &buffer[padd_start], i - padd_start) +
                            write(1, &buffer[ind], length - (1 - padd_start));
        }
    }
    if (extra_c)
        buffer[--ind] = extra_c;
    if (total_written == 0) {
        total_written = write(1, &buffer[ind], length);
    }
    return total_written;
}

