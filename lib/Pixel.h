#ifndef PIXEL_H
#define PIXEL_H

#include "FastLED.h"
#include "Color16.h"

class Pixel {

  public:
    Pixel();
    void setColor(CHSV color);
    void setHue16(uint16_t hue);
    void addHue16(int16_t deltaHue);
    uint16_t getHue16();
    CHSV getColor();
    CHSV16 getHsv16();
    void setHsv16(CHSV16 clr);

    uint8_t x();
    uint8_t y();

    void setXY(uint8_t x, uint8_t y);

  private:
    CHSV16 hsv16;
    uint8_t u[2];
};
#endif
