#ifndef RAINBOW_SEGMENT_H
#define RAINBOW_SEGMENT_H

#include "Effect.h"

class RainbowSegment : public Effect{
  public:
    RainbowSegment();
    void reset();
    void run(Sign &sign, EffectData &data, uint8_t layer);
    bool pushChar(char character, uint8_t layer);
    void signWasUpdated(Sign &sign);
    void randomize(uint8_t ci);

  private:
    bool isStatic;
    bool changeOnBeat;
    int8_t hueStep[LAYER_COUNT];
    int8_t beatStep[LAYER_COUNT];
};
#endif
