#ifndef EFFECT_DATA_H
#define EFFECT_DATA_H

#define FREQ_COUNT 7

#include "Arduino.h"

const uint8_t UINT8_MAX_2 = UINT8_MAX/2;

struct EffectData{
  uint16_t tempo;
  uint8_t rolloff;
  uint16_t volume;
  uint16_t maxVolume;
  uint16_t freqAmp[FREQ_COUNT];
  uint16_t maxFreqAmp[FREQ_COUNT];
};
#endif
