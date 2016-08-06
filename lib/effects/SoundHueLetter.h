#ifndef SOUND_HUE_LETTER_H
#define SOUND_HUE_LETTER_H

#include "Effect.h"

class SoundHueLetter : public Effect {
  public:
    SoundHueLetter();
    void reset():
    void run(Sign &sign, EffectData &data, uint8_t layer);

  private:

};

#endif
