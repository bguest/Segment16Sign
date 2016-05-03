#ifndef SIGN_H
#define SIGN_H

#define LETTERS_COUNT 4
#include "Letter.h"

class Sign{
  public:
    Sign();
    uint16_t pixelCount();
    uint8_t letterCount();
    uint16_t segmentCount();
    void setWord(String word);
    void pushChar(char);
    void setCharacters();
    void pushChar(char, bool);
    void setLayer(uint8_t layer, bool isOn);
    Letter *letters[LETTERS_COUNT];
    Segment *segments[16*LETTERS_COUNT];
    char characters[LETTERS_COUNT];
    bool textChanged;
    bool onBeat;
    void sanitize();

  private:
    uint16_t _pixel_count;
    void _setWord(String word, uint8_t size);
};
#endif
