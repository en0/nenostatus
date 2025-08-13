#include <X11/Xlib.h>

#include "core.h"


static void set_status(OutputStrategy *self, const char *status) {
    XRootOutputStrategy *s = (XRootOutputStrategy *)self;
    XStoreName(s->dpy, s->win, status);
    XFlush(s->dpy);
}

XRootOutputStrategy new_xsetroot_output(const char *display) {
    Display *dpy = XOpenDisplay(display);
    Window win = DefaultRootWindow(dpy);
    return (XRootOutputStrategy) {
        .base.set_status = set_status,
        .dpy = dpy,
        .win = win,
    };
}
