#ifndef WAVE_SEGMENT_H
#define WAVE_SEGMENT_H

#include "Effect.h"

class WavePixels : public Effect{
  public:
    WavePixels();
    void reset();
    void run(Sign &sign, EffectData &data, uint8_t layer);
    bool pushChar(char character, uint8_t layer);
    void invertColors();
    void randomize(uint8_t ci);

  private:
    uint16_t cycleTime[LAYER_COUNT];
    int16_t hueA[LAYER_COUNT];
};

#endif
