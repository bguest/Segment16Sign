#ifndef FADED_XY_H
#define FADED_XY_H

#include "Effect.h"

#define FADED_XY_POINT_COUNT 4

class FadedXY : public Effect{

  public:
    FadedXY();
    void reset();
    void run(Sign &sign, uint8_t layer);

  private:
    uint16_t hue[LAYER_COUNT][FADED_XY_POINT_COUNT];

    void interpolate(Pixel &pixel, uint8_t layer);
};

#endif
