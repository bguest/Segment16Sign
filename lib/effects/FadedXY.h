#ifndef FADED_XY_H
#define FADED_XY_H

#include "Effect.h"

#define FADED_XY_POINT_COUNT 4

class FadedXY : public Effect{

  public:
    FadedXY();
    void reset();
    void run(Sign &sign, EffectData &data, uint8_t layer);
    bool pushChar(char character, uint8_t layer);
    void randomize(uint8_t ci);
    void invertColors();

  private:
    uint16_t hueOffset[LAYER_COUNT];
    int16_t hueOffsetSpeed[LAYER_COUNT];
    uint16_t hue[LAYER_COUNT][FADED_XY_POINT_COUNT];
    int16_t hueSpeed[LAYER_COUNT][FADED_XY_POINT_COUNT];

    void interpolate(Pixel &pixel, uint8_t layer);
};

#endif
