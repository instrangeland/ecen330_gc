#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "sound.h"
#include "tone.h"
#include <stdio.h>

uint8_t *audio = NULL;
uint32_t sample_rate = 0;
// inits the sound buffer and jank
int32_t tone_init(uint32_t sample_hz)
{
    sample_rate = sample_hz;
    if (sample_hz < (DOUBLE_NYQUIST))
        return -1;
    audio = malloc(sizeof(uint8_t) * (sample_hz + 1) / LOWEST_FREQ);
    sound_init(sample_hz);
    return 0;
}

// Free resources used for tone generation (DAC, etc.).
// Return zero if successful, or non-zero otherwise.
int32_t tone_deinit(void)
{
    free(audio);
    sound_deinit();
    return 0;
}

// Start playing the specified tone.
// tone: one of the enumerated tone types.
// freq: frequency of the tone in Hz.
void tone_start(tone_t tone, uint32_t freq)
{
    uint32_t total_samples = sample_rate / freq;
    float val = 0;
    switch (tone)
    {
    case SQUARE_T:
        for (uint32_t t = 0; t < total_samples; t++)
        {
            if (t < (total_samples) / HALF)
            {
                val = MAX_TONE;
            }
            else
            {
                val = 0;
            }
            audio[t] = (uint8_t)val;
            break;
        }
    case SAW_T:
        for (uint32_t t = 0; t < total_samples; t++)
        {
            float adjusted_t;
            if (t < NOT_LAST_QUARTER * (total_samples) / QUARTER)
            {
                adjusted_t = (t + (total_samples / QUARTER));
            }
            else
            {
                adjusted_t = (t - (NOT_LAST_QUARTER * total_samples / QUARTER));
            }
            val = MAX_TONE * (adjusted_t / (total_samples));
            audio[t] = (uint8_t)val;
        }
        break;
    case TRIANGLE_T:
        for (uint32_t t = 0; t < total_samples; t++)
        {
            float adjusted_t;
            if (t < NOT_LAST_QUARTER * (total_samples) / QUARTER)
            {
                adjusted_t = (t + (total_samples / QUARTER));
            }
            else
            {
                adjusted_t = (t - (NOT_LAST_QUARTER * total_samples / QUARTER));
            }
            if (adjusted_t < total_samples / HALF)
            {
                val = MAX_TONE * (adjusted_t / (total_samples / HALF));
            }
            else
            {
                val = MAX_TONE - MAX_TONE * (adjusted_t / (total_samples / HALF));
            }
            audio[t] = (uint8_t)val;
        }
        break;
    case SINE_T:
        for (uint32_t t = 0; t < total_samples; t++)
        {
            float adjusted_t;

            if (t < NOT_LAST_QUARTER * (total_samples) / QUARTER)
            {
                adjusted_t = TAU * (t + (total_samples / QUARTER)) / (total_samples);
            }
            else
            {
                adjusted_t = TAU * (t - (total_samples * NOT_LAST_QUARTER / QUARTER)) / (total_samples);
            }
            val = sinf(adjusted_t) * MAX_TONE;
            audio[t] = (uint8_t)val;
        }
    case LAST_T:
        printf("ERROR PLS HELP WTFETCH");
        break;
    }
    sound_cyclic(audio, total_samples);
}