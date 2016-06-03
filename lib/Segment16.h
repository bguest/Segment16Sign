#ifndef SEGMENT_16_H
#define SEGMENT_16_H

#include "Arduino.h"
#include <FastLED.h>
#include "Sign.h"
#include "Effects.h"
#include "Keyboard.h"
#include "Sound.h"
#include "EffectData.h"

#define SAVED_INPUT_COUNT 2

class Segment16 {
  public:
    Segment16();
    void pushChar(uint32_t character);
    Sign sign;
    CRGB leds[LETTERS_COUNT*(NUM_4_PIXEL*4 + NUM_2_PIXEL*2)];
    void init();
    void run();
    void show();

  private:
    char input[SAVED_INPUT_COUNT];
    bool decideInput(char input);
    bool isInsertMode;

    EffectData data;
    Sound sound;
    Keyboard keyboard;
    Effects effects;

};

#endif
