
#ifndef EFFECT_H
#define EFFECT_H

#define LAYER_COUNT 2     // 0: Foreground 1:Background

#include "Sign.h"

const String CYCLE_TIME_STR = F("(1/Tempo)");
const String FADE_SPEED_STR = F("Fade Speed");
const String CONVERGE_TIME_STR = F("Converge In");
const String SET_SEGS_STR = F("Turn Segments");
const String STEP_SIZE_STR = F("Step Size");
const String NUMBER_ON_STR = F("Number On");
const String HUE_STR = F("Color");
const String SAT_STR = F("Vibrance");
const String VAL_STR = F("Brightness");
const String RESET_STR = F("Reset");
const String INVERTED_STR = F("Inverted");
const String RANDOM_STR = F("Randomized");
const String HUE_AMP_STR = F("Hue Amp");
const String ORIENT_STR = F("Orientation");
const String ON_BEAT_STR = F("Change on Beat");

class Effect{
  public:
    Effect();
    virtual bool pushChar(char character, uint8_t layer);
    virtual bool pushInsert(char character);
    virtual void reset();
    virtual void signWasUpdated(Sign &sign);
    virtual void run(Sign &sign, EffectData &data, uint8_t layer);
    virtual void invertColors();
    virtual void randomize(uint8_t layer);

  protected:
    CHSV color[LAYER_COUNT];
    void randomizeColor(uint8_t layer);
    void off(Sign &sign);
    bool useCharForColor(char character, uint8_t layer);
};
#endif
