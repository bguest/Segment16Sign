#ifndef SOUND_H
#define SOUND_H

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include "EffectData.h"

class Sound {
  public:
    Sound();
    void init();
    void run(EffectData &data);

  private:
    unsigned long lastCollect;
    uint16_t volume;
    uint16_t level[FREQ_COUNT];
    uint16_t maxLevel[FREQ_COUNT];

    AudioInputAnalog       adc;
    AudioAnalyzeFFT256     fft;
    AudioConnection        *patchCord1;

};
#endif
