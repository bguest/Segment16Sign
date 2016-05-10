#ifndef SEGMENT_H
#define SEGMENT_H

#include <stdint.h>
#include "Pixel.h"

#define VERTICAL 0
#define DIAGONAL_RIGHT 1
#define HORIZONTAL 2
#define DIAGONAL_LEFT 3
#define ORIENTATION_COUNT 4

class Segment {
  public:
    Segment();
    void init(Pixel pixels[], uint8_t start, uint8_t endPlus1);
    Pixel *pixels[4];
    bool isOn;
    uint16_t pixelCount();
    void toArray(CRGB array[], uint16_t &currIdx);
    void setColor(CHSV color);
    void setColor(uint8_t layer, CHSV color);
    void setHsv16(CHSV16 color);
    CHSV16 getHsv16();
    void setHsv16(uint8_t layer, CHSV16 color);
    uint8_t index;
    char orientation();

  private:
    uint8_t length;
};

#endif

