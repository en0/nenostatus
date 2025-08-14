#include <X11/Xlib.h>
#include <stdlib.h>

#include "core.h"

static Display *dpy;
static Window win;

static void set_status(OutputStrategy *self, const char *status) {
    XStoreName(dpy, win, status);
    XFlush(dpy);
}

OutputStrategy new_xsetroot_output() {
    char *display = getenv("DISPLAY");
    dpy = XOpenDisplay(display);
    win = DefaultRootWindow(dpy);
    return (OutputStrategy) {.set_status = set_status};
}
