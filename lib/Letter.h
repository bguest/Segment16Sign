#ifndef LETTER_H
#define LETTER_H

#include <stdint.h>
#include "Converter.h"
#include "Segment.h"

/**Represents a sixteen segment single letter, it looks like this
#
#  --- 0 --- --- 1 ---
# |\        |        /|
# | \       |       / |
# |  \      |      /  |
# |   \     |     /   |
# 7    8   11   12    2
# |     \   |   /     |
# |      \  |  /      |
# |       \ | /       |
# |        \|/        |
#  -- 14 --- --- 15 --
# |        /|\        |
# |       / | \       |
# |      /  |  \      |
# |     /   |   \     |
# 6   13   10    9    3
# |   /     |     \   |
# |  /      |      \  |
# | /       |       \ |
# |/        |        \|
#  --- 5 --- --- 4 ---
#
# NOTE: These are the segment numbers
*/

#define NUM_2_PIXEL 10
#define NUM_4_PIXEL 6

class Letter {

  public:
    Letter();
    void init(uint8_t lengths[16]);
    Segment* segment(uint8_t i);
    uint16_t pixelCount();
    void toArray(CRGB array[], uint16_t &currIdx);
    void setChar(char character);
    void setLayer(uint8_t layer, bool isOn);
    void setColor(uint8_t layer, CHSV color);
    CHSV16 getHsv16(uint8_t layer);
    void setHsv16(uint8_t layer, CHSV16 color);
    char currentChar;

  private:
    Pixel pixels[2*NUM_2_PIXEL+4*NUM_4_PIXEL];
    Segment segments[16];
};
#endif
