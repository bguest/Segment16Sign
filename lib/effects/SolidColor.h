#ifndef SOLID_COLOR_H
#define SOLID_COLOR_H

#include "Effect.h"

class SolidColor : public Effect{

  public:
    SolidColor();
    void reset();
    void run(Sign &sign, uint8_t layer);
    bool pushChar(char character, uint8_t layer);
    void randomize(uint8_t ci);

  private:

};
#endif
