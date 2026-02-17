#include <signal.h>
#include <stdio.h>

#include "core.h"

static MetricCollector* installed_signals[NSIG] = {0};

static void signal_handler(int rtsig) {
    fprintf(stderr, "Got a signal: %d\n", rtsig);
    MetricCollector* collector = installed_signals[rtsig];
    collector->update(collector);
}

MetricCollector *periodic(MetricCollector* collector, const int interval) {
    if (interval > 0) {
        for (int i = 0; i < sizeof(installed_signals)/sizeof(MetricCollector*); i++) {
            if (installed_signals[i] == collector) {
                fprintf(stderr, "Error: Cannot schedule a MetricCollector while it is bound to a signal handler.\n");
                exit(103);
            }
        }
    }

    collector->interval[0] = interval;
    collector->interval[1] = interval;
    return collector;
}

MetricCollector *onsignal(MetricCollector* collector, const int rtsig) {
    struct sigaction sa = {.sa_handler = &signal_handler};
    if (rtsig > SIGRTMAX || rtsig < SIGRTMIN) {
        fprintf(stderr, "Failed to install signal %d. Signal must be between %d and %d.", rtsig, SIGRTMIN, SIGRTMAX);
        exit(100);
    } else if (installed_signals[rtsig] != NULL) {
        fprintf(stderr, "Failed to install signal %d. Already in use.", rtsig);
        exit(101);
    } if (sigaction(rtsig, &sa, NULL) == -1) {
        fprintf(stderr, "Failed to install signal %d. Unknown Error.", rtsig);
        exit(102);
    }
    fprintf(stderr, "Installed signale handler: '%d'.\n", rtsig);
    installed_signals[rtsig] = collector;
    return periodic(collector, 0);
}
