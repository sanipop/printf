Task 0: Handling Basic Conversion Specifiers %c, %s, and %%
Implement the basic functionality of printing characters (%c), strings (%s), and the literal '%' character (%%) according to the provided format.

Task 1: Handling Conversion Specifiers %d and %i
Extend the _printf function to handle printing integers (%d and %i conversion specifiers).

Task 2: Handling Custom Conversion Specifier %b (Binary)
Add support for a custom conversion specifier %b, which converts an unsigned integer argument to binary representation.

Task 3: Handling Conversion Specifiers %u, %o, %x, and %X
Extend the _printf function to handle printing unsigned integers (%u), octal integers (%o), lowercase hexadecimal integers (%x), and uppercase hexadecimal integers (%X).

Task 4: Optimizing Output with Local Buffer
Use a local buffer of 1024 characters to minimize the number of calls to the write function for more efficient output.

Task 5: Handling Custom Conversion Specifier %S (Printable String)
Implement a custom conversion specifier %S to print strings while escaping non-printable characters.

Task 6: Handling Conversion Specifier %p (Pointer)
Add support for the %p conversion specifier to print pointers.

Task 7: Handling Flag Characters +, space, and #
Handle flag characters for non-custom conversion specifiers: + for signed numbers, space for positive numbers with space padding, and # for alternative formatting.

Task 8: Handling Length Modifiers l and h
Implement the length modifiers l (long) and h (short) for non-custom conversion specifiers.

Task 9: Handling Field Width
Extend the _printf function to handle the field width for non-custom conversion specifiers.

Task 10: Handling Precision
Add support for precision (number of decimal places) for non-custom conversion specifiers.

Task 11: Handling Flag Character 0
Implement the 0 flag character for non-custom conversion specifiers, which pads with zeros.

Task 12: Handling Flag Character -
Handle the - flag character for left-aligning output.

Task 13: Handling Custom Conversion Specifier %r (Reversed String)
Implement a custom conversion specifier %r to print reversed strings.

Task 14: Handling Custom Conversion Specifier %R (ROT13 String)
Add support for a custom conversion specifier %R to print strings in ROT13-encoded form.

Task 15: Combining All Options
Ensure that all the above options work seamlessly together in the _printf function.
