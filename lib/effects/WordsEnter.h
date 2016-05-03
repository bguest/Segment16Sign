#ifndef WORDS_ENTER_H
#define WORDS_ENTER_H

#include "Effect.h"

const uint8_t WORDS_COUNT = 20;

class WordsEnter : public Effect{

  public:
    WordsEnter();
    void reset();
    void run(Sign &sign, uint8_t layer);
    bool pushInsert(char character);
    bool pushChar(char character, uint8_t layer);
    void randomize(uint8_t ci);

  private:
    void pushBuffer();
    void pushToBuffer(char character);
    void backspaceBuffer();
    void softReset();
    uint8_t numBeats;
    uint8_t beatIdx;
    uint8_t wordIdx;
    uint8_t wordsCount;
    uint8_t letterIdx;
    char buffer[LETTERS_COUNT];
    char words[WORDS_COUNT][LETTERS_COUNT];
};

#endif
