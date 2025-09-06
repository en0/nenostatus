#include "collectors/thermal.h"
#include "core.h"
#include <stdio.h>

#define ALARM_VALUE 95000
const char *ICON_SET[] = { "", "", "", "", "" };

static const char* get_icon(int value) {
    if (value < 40000)
        return ICON_SET[0];
    else if (value < 60000)
        return ICON_SET[1];
    else if (value < 75000)
        return ICON_SET[2];
    else if (value < 85000)
        return ICON_SET[3];
    else
        return ICON_SET[4];
}

static inline void notify_if(ThermalCollector *self, int temp) {
    if (temp >= ALARM_VALUE && !self->alarmed) {
        self->alarmed = true;
        notify_critical(NULL, "Thermal Alert", "Temperature is too high!");
    } else if (temp < ALARM_VALUE && self->alarmed) {
        self->alarmed = false;
    }
}

static void update(MetricCollector *self) {
    ThermalCollector *s = (ThermalCollector *)self;
    FILE *fp = fopen(s->hw_path, "r");
    if (fp == NULL) {
        snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "COLLECTOR ERROR: file not found");
        return;
    }

    int temp;
    if (fscanf(fp, "%d", &temp) != 1) {
        snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "COLLECTOR ERROR");
        return;
    }

    notify_if(s, temp);
    snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "%s %d󰔄", get_icon(temp), temp / 1000);
}

ThermalCollector new_thermal_collector(const int interval, const char *hw_path) {
    ThermalCollector ret = {0};
    initialize_collector_base(&ret.base, interval, update);
    ret.hw_path = hw_path;
    ret.alarmed = false;
    return ret;
}
