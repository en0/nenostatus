#include <stdio.h>
#include <stdarg.h>

int append_to_buffer(char *buffer, size_t buffer_size, size_t *offset, const char *format, ...) {

    size_t remaining_space = buffer_size - *offset;

    // Check for full buffer
    if (*offset >= buffer_size) return -1;

    va_list args;
    va_start(args, format);
    int written = vsnprintf(buffer + *offset, remaining_space, format, args);
    va_end(args);

    // Check for write error
    if (written < 0 || (size_t)written >= remaining_space) return -1;

    // Update offset and return the number of written chars.
    *offset += written;
    return written;
}
