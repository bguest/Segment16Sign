#ifndef SCROLLING_H
#define SCROLLING_H

#include "Effect.h"

const uint8_t SCROLL_LENGTH = 100;

class Scrolling : public Effect {

  public:
    Scrolling();
    void reset();
    void run(Sign &sign, EffectData &data, uint8_t layer);
    bool pushInsert(char character);
    bool pushChar(char character, uint8_t layer);
    void randomize(uint8_t ci);

  private:
    void pushToBuffer(char character);
    void shiftLeft();
    void backspaceBuffer();
    void softReset();
    void setRandomBuffer();
    void setRandomLetter(char word[4]);

    uint8_t numBeats;
    uint8_t beatIdx;
    uint8_t startIdx;
    uint8_t charCount;
    char buffer[SCROLL_LENGTH];
    int8_t randomLetterIdx;

};
#endif

