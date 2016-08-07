#ifndef SEIZURE_H
#define SEIZURE_H

#include "Effect.h"

#define SEIZURE_COLOR_COUNT 4

class Seizure : public Effect{
  public:
    Seizure();
    void reset();
    void run(Sign &sign, EffectData &data, uint8_t layer);
    bool pushChar(char character, uint8_t layer);
    void randomize(uint8_t ci);

  private:
    CHSV colors[SEIZURE_COLOR_COUNT][LAYER_COUNT];
    uint8_t editIdx;
    uint8_t colorIdx[LAYER_COUNT];
    uint8_t flashPerBeat[LAYER_COUNT];
    unsigned long lastChange[LAYER_COUNT];

};

#endif
