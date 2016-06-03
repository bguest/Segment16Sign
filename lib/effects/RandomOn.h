#ifndef RANDOM_ON_H
#define RANDOM_ON_H

#include "Effect.h"

class RandomOn : public Effect{

  public:
    RandomOn();
    void reset();
    void run(Sign &sign, EffectData &data, uint8_t layer);
    bool pushChar(char character, uint8_t layer);
    void randomize(uint8_t ci);

  private:
    uint8_t onCount;
    bool shouldReset;
    bool turnOn;

};
#endif
