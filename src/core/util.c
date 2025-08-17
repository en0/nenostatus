#include <math.h>
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

void render_bar(char *buffer, size_t buffer_size, double value, double max_value) {

    // Calculate the effective size for the progress bar, which is one-third
    // of the buffer size minus one for the null terminator.
    size_t buffer_size_3rd = (buffer_size-1) / 3;
    int v = round(value * buffer_size_3rd / (double)max_value);

    for (int i = 0; i < buffer_size_3rd; i++) {

        // Define three indices for each segment of the progress bar, as each
        // Unicode character occupies three bytes.
        int i0 = (i * 3) + 0;
        int i1 = (i * 3) + 1;
        int i2 = (i * 3) + 2;

        // Assign the first two bytes for the Unicode character
        // representation of the progress bar.
        buffer[i0] = '\xEE';
        buffer[i1] = '\xB8';

        // Determine the character to display based on the current index and the
        // calculated value, differentiating between filled and unfilled segments.
        if (i < v) {
            if (i == 0) buffer[i2] = '\x83';
            else if (i == buffer_size_3rd - 1) buffer[i2] = '\x85';
            else buffer[i2] = '\x84';
        } else {
            if (i == 0) buffer[2] = '\x80';
            else if (i == buffer_size_3rd - 1) buffer[i2] = '\x82';
            else buffer[i2] = '\x81';
        }
    }

    // Set the last byte of the buffer to null terminator to mark the end of the string.
    buffer[buffer_size-1] = 0;
}
