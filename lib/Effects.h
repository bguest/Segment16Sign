#ifndef EFFECTS_H
#define EFFECTS_H

#include "Sign.h"
#include "Helpers.h"
#include "effects/Effect.h"
#include "effects/RandomOn.h"
#include "effects/Counter.h"
#include "effects/BasicTyping.h"
#include "effects/WordsEnter.h"
#include "effects/SolidColor.h"
#include "effects/SolidFade.h"
#include "effects/RandomFade.h"
#include "effects/RandomLetters.h"
#include "effects/RainbowLetter.h"
#include "effects/RainbowSegment.h"
#include "effects/FadeTo.h"
#include "effects/WavePixels.h"
#include "effects/LinesOn.h"
#include "effects/Clock.h"
#include "effects/RandomScroll.h"

#define BASIC_TYPING 0
#define RANDOM_ON 1
#define COUNTER 2
#define RANDOM_LETTERS 3
#define WORDS_ENTER 4
#define LINES_ON 5
#define CLOCK 6
#define RANDOM_SCROLL 7
#define TEXT_EFFECTS_COUNT 8

#define SOLID_COLORS 0
#define SOLID_FADE 1
#define RANDOM_FADE 2
#define RAINBOW_LETTER 3
#define RAINBOW_SEGMENT 4
#define FADE_TO 5
#define WAVE_PIXELS 6
#define COLOR_EFFECTS_COUNT 7

class Effects {
  public:
    Effects();
    bool pushInsert(char character);
    void pushChar(char character);
    void signWasUpdated(Sign &sign);
    void run(Sign &sign);

  private:
    RandomOn randomOn;
    BasicTyping basicTyping;
    Counter counter;
    RandomLetters randomLetters;
    WordsEnter wordsEnter;
    Clock clock;
    LinesOn linesOn;
    RandomScroll randomScroll;

    SolidColor solidColor;
    RandomFade randomFade;
    SolidFade solidFade;
    RainbowLetter rainbowLetter;
    RainbowSegment rainbowSegment;
    FadeTo fadeTo;
    WavePixels wavePixels;

    Effect nullEffect;
    uint8_t curLayer;

    uint8_t cTextEffect;
    Effect *textEffect;
    uint8_t cColorEffect[LAYER_COUNT];
    Effect *colorEffect[LAYER_COUNT];

    unsigned long lastTouched;
    unsigned long lastRun;
    uint16_t cycleTime;
    unsigned long textLastRun;
    uint16_t textCycleTime;
    bool changeText;

    void reset();
    void setDefaults();
    uint8_t randomizeLayer;
    uint32_t randomizeTime;
    void randomize();

    uint8_t nextTextEffect();
    uint8_t prevTextEffect();
    void updateTextEffect();

    uint8_t nextColorEffect(uint8_t layer);
    uint8_t prevColorEffect(uint8_t layer);
    void updateColorEffect(uint8_t layer);
    void invertColors();
};

#endif
