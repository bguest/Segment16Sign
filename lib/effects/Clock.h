#ifndef CLOCK_H
#define CLOCK_H

#include "Effect.h"
class Clock : public Effect{
  public:
    Clock();
    void reset();
    void run(Sign &sign, EffectData &data, uint8_t layer);
    bool pushChar(char character, uint8_t layer);
  private:
    bool isClock; //As Apposed to Timer
    bool is24Hour;
    uint16_t stepTime;
    int16_t minutesOffset;
    int16_t hoursOffset;
    unsigned long lastUpdated;
    int16_t timeAmpMinutes;
    uint16_t dilationPeriodMinutes;
};

#endif
