#define FADE_TIME_STEP 5
#include "RandomFade.h"

RandomFade::RandomFade(){
  this -> reset();
}

void RandomFade::reset(){
  fadeTime = 800;
  for(uint8_t i=0; i<LAYER_COUNT; i++){
    color[i] = CHSV(128*i,255,255);
    fadeSpeed[i] = (-40*i)+20;
  }
  this -> randomizeSpeeds();
}

void RandomFade::randomize(uint8_t ci){
  fadeTime = random(0,1000);
  this -> randomizeColor(ci);
  fadeSpeed[ci] = random(-100,100);
  this -> randomizeSpeeds();
}

void RandomFade::run(Sign &sign, EffectData &data, uint8_t ci){
  if( sign.textChanged ){ this -> recalculateSpeeds(sign); }
  uint16_t seg_count = sign.segmentCount();
  CHSV clr = color[ci];

  bool on = (ci == 0);

  for(uint8_t i=0; i < seg_count; i++){
    Segment currSeg = *sign.segments[i];
    if(currSeg.isOn == on){
      segHue[i] += segSpeed[i];
      clr.hue = (uint8_t)(segHue[i] >> 8);
      currSeg.setColor(clr);
    }
  }
}

bool RandomFade::pushChar(char character, uint8_t ci){
  if( this -> useCharForColor(character, ci)){ return true; };

  int32_t val = 0xFFFF;
  String desc;

  switch(character){
    case 'r': val = 1; this->randomizeSpeeds();
              desc = RESET_STR; break;
    case 'f': val = this -> incRandomSpeed(true, ci);
              desc = FADE_SPEED_STR; break;
    case 's': val = this -> incRandomSpeed(false, ci);
              desc = FADE_SPEED_STR; break;
    case 'S': val = (fadeTime += FADE_TIME_STEP);
              desc = CONVERGE_TIME_STR; break;
    case 'F': val = (fadeTime -= FADE_TIME_STEP);
              desc = CONVERGE_TIME_STR; break;
    case 'x': this -> randomize(ci);
              val = fadeSpeed[ci];
              desc = RANDOM_STR; break;
  }
  return( usedSetting(desc, val) );
}

int16_t RandomFade::incRandomSpeed(bool isPositive, uint8_t layer){

  if(isPositive){
    fadeSpeed[layer]++;
  }else{
    fadeSpeed[layer]--;
  }
  this -> randomizeSpeeds();

  return fadeSpeed[layer];
}

void RandomFade::randomizeSpeeds(){

  int16_t mn = min(fadeSpeed[0], fadeSpeed[1]);
  int16_t mx = max(fadeSpeed[0], fadeSpeed[1]);
  for(uint8_t i=0; i < 16*LETTERS_COUNT; i++){
    segSpeed[i] = random(mn, mx);
  }
}

// Called when new letters pushed to sign
void RandomFade::signWasUpdated(Sign &sign){
  this -> recalculateSpeeds(sign);
}

void RandomFade::recalculateSpeeds(Sign &sign){
  uint16_t seg_count = sign.segmentCount();
  uint16_t hue_final[LAYER_COUNT];

  for(uint8_t i=0; i<LAYER_COUNT; i++){
    hue_final[i] = (uint16_t)(color[i].hue << 8);
  }

  for(uint16_t i=0; i< seg_count; i++){
    Segment currSeg = *sign.segments[i];
    uint8_t ci = currSeg.isOn ? 0 : 1;
    segSpeed[i] = (hue_final[ci] - segHue[i])/fadeTime;
  }
}
