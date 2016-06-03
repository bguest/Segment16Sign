#ifndef SOLID_FADE_H
#define SOLID_FADE_H

#include "Effect.h"

class SolidFade : public Effect{
  public:
    SolidFade();
    void reset();
    void run(Sign &sign, EffectData &data, uint8_t layer);
    bool pushChar(char character, uint8_t layer);
    void invertColors();
    void randomize(uint8_t ci);

  private:
    uint16_t fadeHue[LAYER_COUNT];
    uint16_t fadeSpeed[LAYER_COUNT];
    uint8_t letterStep[LAYER_COUNT];
    int16_t incSegSpeed(bool isPositive, uint8_t layer);
};
#endif
