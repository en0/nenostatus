#include "collectors/shell.h"
#include "core.h"
#include <stdio.h>
#include <string.h>

static void update(MetricCollector *self) {

    ShellCollector *s = (ShellCollector *)self;
    FILE *fp;
    fp = popen(s->path, "r");

    if (fp != NULL) {
        fgets(self->status, MAX_COLLECTOR_STATUS_SIZE, fp);
        self->status[strcspn(self->status, "\n")] = '\0';
    } else
        snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "COLLECTOR ERROR: File not found.");
    pclose(fp);
}

ShellCollector new_shell_collector(const char *path) {
    ShellCollector ret = {.path=path};
    initialize_collector_base(&ret.base, update);
    return ret;
}
