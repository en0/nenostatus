#include <stdio.h>
#include <stdbool.h>
#include <alsa/asoundlib.h>

#include "collectors/audio_state.h"
#include "core.h"

static void update(MetricCollector *self) {
    AudioStateCollector *s = (AudioStateCollector *)self;
    snd_mixer_t *mixer;
    snd_mixer_elem_t *out_elem;
    snd_mixer_elem_t *in_elem;
    snd_mixer_selem_id_t *out_sid;
    snd_mixer_selem_id_t *in_sid;
    int out_mute, in_mute;
    char status_buffer[MAX_COLLECTOR_STATUS_SIZE];

    // Create a simple mixer element ID
    snd_mixer_selem_id_alloca(&out_sid);
    snd_mixer_selem_id_set_name(out_sid, s->output_name);

    snd_mixer_selem_id_alloca(&in_sid);
    snd_mixer_selem_id_set_name(in_sid, s->input_name);

    // Open the mixer
    if (snd_mixer_open(&mixer, 0) < 0) {
        snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "COLLECTOR ERROR: Failed to open mixer");
        return;
    }

    // Attach the mixer to the specified device
    if (snd_mixer_attach(mixer, s->mixer_name) < 0 || snd_mixer_selem_register(mixer, NULL, NULL) < 0 || snd_mixer_load(mixer) < 0) {
        snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "COLLECTOR ERROR: Failed to attach to mixer");
        snd_mixer_close(mixer);
        return;
    }

    // Find the mixer element
    out_elem = snd_mixer_find_selem(mixer, out_sid);
    if (!out_elem) {
        snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "COLLECTOR ERROR: Output element not found");
        snd_mixer_close(mixer);
        return;
    }

    // Get the mute state
    snd_mixer_selem_get_playback_switch(out_elem, SND_MIXER_SCHN_FRONT_LEFT, &out_mute);

    // Find the mixer element
    in_elem = snd_mixer_find_selem(mixer, in_sid);
    if (!in_elem) {
        snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "COLLECTOR ERROR: Input element not found");
        snd_mixer_close(mixer);
        return;
    }

    // Get the mute state
    snd_mixer_selem_get_capture_switch(in_elem, SND_MIXER_SCHN_MONO, &in_mute);

    // Format the status string
    snprintf(status_buffer, MAX_COLLECTOR_STATUS_SIZE, "%s%s", in_mute == 0 ? "󰍭" : "󰍬", out_mute == 0 ? " " : " ");
    snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "%s", status_buffer);

    // Clean up
    snd_mixer_close(mixer);
}

AudioStateCollector new_audio_state_collector(const char *mixer_name, const char *output_name, const char *input_name) {
    AudioStateCollector ret = {.mixer_name = mixer_name, .output_name=output_name, .input_name = input_name};
    initialize_collector_base(&ret.base, "Audo Status Collector", 1, update);
    return ret;
}
