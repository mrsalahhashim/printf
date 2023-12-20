#include "main.h"
void print_buffer(char buffer[], int *buff_ind);

int _printf(const char *format, ...) {
    // Variable declarations
    int i, printed = 0, printed_chars = 0;
    int flags, width, precision, size, buff_ind = 0;
    va_list list;
    char buffer[BUFF_SIZE];

    // Check if the format string is NULL
    if (format == NULL)
        return (-1);

    va_start(list, format); // Initialize the va_list

    // Loop through the format string
    for (i = 0; format && format[i] != '\0'; i++) {
        if (format[i] != '%') {
            // If the current character is not '%', add it to the buffer
            buffer[buff_ind++] = format[i];
            if (buff_ind == BUFF_SIZE)
                print_buffer(buffer, &buff_ind); // Print the buffer if it's full
            printed_chars++; // Increment the count of printed characters
        } else {
            // If the current character is '%', handle the format specifier
            print_buffer(buffer, &buff_ind); // Print the buffer before handling the specifier
            flags = get_flags(format, &i); // Get flags (not implemented here)
            width = get_width(format, &i, list); // Get width (not implemented here)
            precision = get_precision(format, &i, list); // Get precision (not implemented here)
            size = get_size(format, &i); // Get size (not implemented here)
            ++i;
            // Handle printing based on the format specifier
            printed = handle_print(format, &i, list, buffer, flags, width, precision, size);
            if (printed == -1)
                return (-1); // Error handling
            printed_chars += printed; // Increment the count of printed characters
        }
    }

    print_buffer(buffer, &buff_ind); // Print the remaining buffer content
    va_end(list); // Clean up the va_list
    return (printed_chars); // Return the total count of printed characters
}

void print_buffer(char buffer[], int *buff_ind) {
    // Print the contents of the buffer if it's not empty
    if (*buff_ind > 0)
        write(1, &buffer[0], *buff_ind);
    *buff_ind = 0; // Reset the buffer index to 0
}

