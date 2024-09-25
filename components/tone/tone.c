#include <stdint.h>
#include "sound.h"
#include "tone.h"
int32_t tone_init(uint32_t sample_hz)
{
    return 0;
}

// Free resources used for tone generation (DAC, etc.).
// Return zero if successful, or non-zero otherwise.
int32_t tone_deinit(void)
{
    return 0;
}

// Start playing the specified tone.
// tone: one of the enumerated tone types.
// freq: frequency of the tone in Hz.
void tone_start(tone_t tone, uint32_t freq)
{
    return;
}