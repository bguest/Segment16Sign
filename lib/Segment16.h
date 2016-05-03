#ifndef SEGMENT_16_H
#define SEGMENT_16_H

#include "Arduino.h"
#include <FastLED.h>
#include "Sign.h"
#include "Effects.h"

#define SAVED_INPUT_COUNT 2

class Segment16 {
  public:
    Segment16();
    void pushChar(uint32_t character);
    Sign sign;
    CRGB *leds;
    void init();
    void show(void);

  private:
    char input[SAVED_INPUT_COUNT];
    bool decideInput(char input);
    bool isInsertMode;
    Effects effects;
};

#endif
