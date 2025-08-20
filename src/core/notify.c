#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "core.h"

#define CMD_BUFFER_SIZE 255

static inline void send_notify(const char *urgency, const char *icon, const char *title, const char *message) {
    char buffer[CMD_BUFFER_SIZE] = {0};
    snprintf(
        buffer,
        sizeof(buffer),
        "notify-send -u %s -i \"%s\" \"%s\" \"%s\"",
        urgency,
        icon == NULL ? "user-info" : icon,
        title,
        message
    );
    system(buffer);
}

void notify_low(const char *icon, const char *title, const char *message) {
    send_notify("low", icon, title, message);
}

void notify_normal(const char *icon, const char *title, const char *message) {
    send_notify("normal", icon, title, message);
}

void notify_critical(const char *icon, const char *title, const char *message) {
    send_notify("critical", icon, title, message);
}
