#ifndef COUNTER_H
#define COUNTER_H

#include "Effect.h"
class Counter : public Effect{
  public:
    Counter();
    void reset();
    void run(Sign &sign, EffectData &data, uint8_t layer);
    bool pushChar(char character, uint8_t layer);
    void randomize(uint8_t ci);
  private:
    int step;
    uint16_t count;
};

#endif
