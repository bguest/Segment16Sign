#ifndef LINES_ON_H
#define LINES_ON_H

#include "Effect.h"

class LinesOn : public Effect{

  public:
    LinesOn();
    void reset();
    void run(Sign &sign, uint8_t layer);
    bool pushChar(char character, uint8_t layer);
    void randomize(uint8_t ci);

  private:
    char orientation;
    bool changeOnBeat;
    void incOrient();

};

#endif

