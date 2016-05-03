#ifndef RAINBOW_LETTER_H
#define RAINBOW_LETTER_H

#include "Effect.h"

class RainbowLetter : public Effect{
  public:
    RainbowLetter();
    void reset();
    void run(Sign &sign, uint8_t layer);
    bool pushChar(char character, uint8_t layer);
    void signWasUpdated(Sign &sign);
    void signWasUpdated(Sign &sign, uint8_t layer);
    void randomize(uint8_t ci);

  private:
    bool isStatic;
    bool changeOnBeat;
    int8_t hueStep[LAYER_COUNT];
    uint16_t cycleTime[LAYER_COUNT];
    int16_t hueA[LAYER_COUNT];
};
#endif
