#ifndef FADE_TO_H
#define FADE_TO_H

#include "Effect.h"

class FadeTo : public Effect{

  public:
    FadeTo();
    void reset();
    void run(Sign &sign, uint8_t layer);
    bool pushChar(char character, uint8_t layer);
    void randomize(uint8_t ci);

  private:
    uint16_t fadeTime;
    uint16_t segHue[16*LETTERS_COUNT];
};
#endif
