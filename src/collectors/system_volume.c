#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <alsa/asoundlib.h>

#include "collectors/system_volume.h"
#include "core.h"

static void update(MetricCollector *self) {
    SystemVolumeCollector *s = (SystemVolumeCollector *)self;
    snd_mixer_t *mixer;
    snd_mixer_elem_t *elem;
    snd_mixer_selem_id_t *sid;
    long volume, min_volume, max_volume;
    int mute;
    char status_buffer[MAX_COLLECTOR_STATUS_SIZE];

    // Create a simple mixer element ID
    snd_mixer_selem_id_alloca(&sid);
    snd_mixer_selem_id_set_name(sid, s->element_name);

    // Open the mixer
    if (snd_mixer_open(&mixer, 0) < 0) {
        snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "COLLECTOR ERROR");
        return;
    }

    // Attach the mixer to the specified device
    if (snd_mixer_attach(mixer, s->mixer_name) < 0 || snd_mixer_selem_register(mixer, NULL, NULL) < 0 || snd_mixer_load(mixer) < 0) {
        snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "COLLECTOR ERROR");
        snd_mixer_close(mixer);
        return;
    }

    // Find the mixer element
    elem = snd_mixer_find_selem(mixer, sid);
    if (!elem) {
        snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "COLLECTOR ERROR: Element not found");
        snd_mixer_close(mixer);
        return;
    }

    // Get the volume and mute state
    snd_mixer_selem_get_playback_volume_range(elem, &min_volume, &max_volume);
    snd_mixer_selem_get_playback_volume(elem, SND_MIXER_SCHN_FRONT_LEFT, &volume);
    snd_mixer_selem_get_playback_switch(elem, SND_MIXER_SCHN_FRONT_LEFT, &mute);

    // Compute volume percentage.
    int vol_perc = round((volume - min_volume) / (double)max_volume * 100);

    // Format the status string
    snprintf(status_buffer, MAX_COLLECTOR_STATUS_SIZE, "%s %i%%", mute == 0 ? " " : " ", vol_perc);
    snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "%s", status_buffer);

    // Clean up
    snd_mixer_close(mixer);
}

SystemVolumeCollector new_system_volume_collector(const char *mixer_name, const char *element_name) {
    SystemVolumeCollector ret = {.mixer_name = mixer_name, .element_name = element_name};
    initialize_collector_base(&ret.base, "System Volume Collector", 1, update);
    return ret;
}
