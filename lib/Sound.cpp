#include "Arduino.h"
#include "Sound.h"

#define STROBE A0
#define RESET A3
#define AUDIO_OUT A1
#define AUDIO_RAW A2
#define USE_RAW_VOLUME 1

const uint8_t ROLLOFF_DURRATION = 5;

void Sound::init(){

  //Set spectrum Shield pin configurations
  pinMode(STROBE, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(AUDIO_OUT, INPUT);
  digitalWrite(STROBE, HIGH);
  digitalWrite(RESET, HIGH);

  //Initialize Spectrum Analyzers
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, HIGH);
  delay(1);
  digitalWrite(STROBE, HIGH);
  delay(1);
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, LOW);

  for(uint8_t i=0; i<7; i++){
    freqAmp[i] = 0;
  }
  lastCollect = 0;
}

void Sound::run(EffectData &data){

  uint16_t currAmp;
  uint16_t currVolume = 0;

  digitalWrite(RESET, HIGH);
  //digitalWrite(STROBE, HIGH);
  //delayMicroseconds(18);
  //digitalWrite(STROBE, LOW);
  //delayMicroseconds(18);
  delayMicroseconds(4);
  digitalWrite(RESET, LOW);
  digitalWrite(STROBE, HIGH);

  for(uint8_t i = 0; i<FREQ_COUNT; i++) {
    delayMicroseconds(19);
    digitalWrite(STROBE, LOW);
    delayMicroseconds(30);

    currAmp = ( analogRead(AUDIO_OUT) + analogRead(AUDIO_OUT) )/2;
    if (currAmp > freqAmp[i]){
      freqAmp[i] = currAmp;
    }
    delayMicroseconds(20);
    digitalWrite(STROBE, HIGH);
  }
  //delayMicroseconds(18);
  //digitalWrite(STROBE, LOW);

#if USE_RAW_VOLUME == 1
  currVolume = ( analogRead(AUDIO_RAW) + analogRead(AUDIO_RAW) )/2;
#else
  for(uint8_t i=0; i<FREQ_COUNT; i++){
    currVolume += freqAmp[i];
  }
#endif
  if(currVolume > volume){
    volume = currVolume;
  }

  // Debug Stuff
  //for(uint8_t i=0; i<FREQ_COUNT; i++){
    //Serial.print(freqAmp[i]);
    //Serial.print(" ");
  //}
  //Serial.println();

  // Update if > Sound collect time
  unsigned long currMillis = millis();

  if(currMillis - lastCollect > ROLLOFF_DURRATION){
    lastCollect = currMillis;

    for(uint8_t i = 0; i<FREQ_COUNT; i++) {
      if(freqAmp[i] > data.freqAmp[i]){
        data.freqAmp[i] = freqAmp[i];
      }else{
        data.freqAmp[i] = (data.freqAmp[i]*data.rolloff)/200;
      }

      if(freqAmp[i] > data.maxFreqAmp[i]){
        data.maxFreqAmp[i] = freqAmp[i];
      }
      freqAmp[i] = 0;
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


