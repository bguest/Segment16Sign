#ifndef RANDOM_SCROLL_H
#define RANDOM_SCROLL_H

#include "Effect.h"

class RandomScroll : public Effect{
  public:
    RandomScroll();
    void reset();
    void run(Sign &sign, EffectData &data, uint8_t layer);
    bool pushChar(char character, uint8_t layer);

  private:
};
#endif
