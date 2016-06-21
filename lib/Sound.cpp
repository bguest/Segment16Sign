#include "Arduino.h"
#include "Sound.h"

#define AUDIO_RAW A2

const uint8_t ROLLOFF_DURRATION = 5;

Sound::Sound(){
  patchCord1 = new AudioConnection(adc, fft);
}

void Sound::init(){
  for(uint8_t i=0; i<FREQ_COUNT; i++){
    level[i] = 0;
    maxLevel[i] = 0;
  }
  lastCollect = 0;
  AudioMemory(10);
  fft.windowFunction(AudioWindowHanning1024);
  fft.averageTogether(1);
}

void Sound::run(EffectData &data){

  uint8_t bands[FREQ_COUNT][2] = {
    {   0,   0},
    {   1,   2},
    {   3,   5},
    {   6,  11},
    {  12,  21},
    {  22,  39},
    {  40,  70},
    {  71, 126}
  };

  if( fft.available() ){
    for(uint8_t i=0; i<FREQ_COUNT; i++){
      uint16_t val = 0;
      for(uint8_t j = bands[i][0]; j <= bands[i][1]; j++ ){
        val += fft.output[j];
      }
      level[i] = val;
    }
  }

  for(uint8_t i=0; i<FREQ_COUNT; i++){
    if(level[i] > maxLevel[i]){
      maxLevel[i] = level[i];
    }
  }

  // Update if > Sound collect time
  unsigned long currMillis = millis();

  if(currMillis - lastCollect > ROLLOFF_DURRATION){
    lastCollect = currMillis;

    volume = 0;

    for(uint8_t i = 0; i<FREQ_COUNT; i++) {
      if(maxLevel[i] > data.freqAmp[i]){
        data.freqAmp[i] = maxLevel[i];
      }else{
        data.freqAmp[i] = (data.freqAmp[i]*data.rolloff)/200;
      }
      volume += data.freqAmp[i];

      if(maxLevel[i] > data.maxFreqAmp[i]){
        data.maxFreqAmp[i] = maxLevel[i];
      }
      maxLevel[i] = 0;
    }

    if(volume > data.volume){
      data.volume = volume;
    }else{
      data.volume = (data.volume*data.rolloff)/200;
    }

    if(volume > data.maxVolume){
      data.maxVolume = volume;
    }
    volume = 0;
  }

}


/*
  if(currMillis - lastCollect > 500){
    lastCollect = currMillis;
    Serial.print("Max Memory:");
    Serial.println(AudioMemoryUsageMax());
    Serial.print(" cpu:");
    Serial.println(AudioProcessorUsageMax());

    for(uint8_t i = 0; i<FREQ_COUNT; i++) {
      Serial.print(level[i]);
      Serial.print(" ");
    }
    Serial.println();

    for(uint8_t i = 0; i<FREQ_COUNT; i++) {
      Serial.print(maxLevel[i]);
      Serial.print(" ");
      maxLevel[i] = maxLevel[i]*0.9;
    }
    Serial.println();
  }
*/
