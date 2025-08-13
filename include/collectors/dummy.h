#ifndef COLLECTORS_DUMMY_H
#define COLLECTORS_DUMMY_H

#include "core.h"


/**
 * Dummy
 * A collector that does nothing.
 *
 * Members:
 *
 * - MetricCollector base
 *   Inheret the base class.
 *
 * - int v
 *   Just a value to put in the status
 */
typedef struct DummyCollector DummyCollector;
struct DummyCollector {
    MetricCollector base;
    int v;
};

/**
 * A collector that does nothing.
 */
DummyCollector new_dummy_collector(const char *name, int v);

#endif
