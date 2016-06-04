#ifndef WAVE_XY_H
#define WAVE_XY_H

#include "Effect.h"

class WaveXY : public Effect{

  public:
    WaveXY();
    void reset();
    void run(Sign &sign, EffectData &data, uint8_t layer);
    bool pushChar(char character, uint8_t layer);
    void randomize(uint8_t ci);
    void invertColors();

  private:
    uint8_t freq[2][LAYER_COUNT];
    int8_t step[2][LAYER_COUNT];
    uint16_t offset[2][LAYER_COUNT];
    bool isWaveValue;

    void calculate(Pixel &pixel, uint8_t layer);
};

#endif

