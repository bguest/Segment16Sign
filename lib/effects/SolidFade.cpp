#include "SolidFade.h"

SolidFade::SolidFade(){
  this -> reset();
}

void SolidFade::reset(){
  for(uint8_t i=0; i<LAYER_COUNT; i++){
    color[i] = CHSV(128*i,255,255);
    fadeHue[i] = 0;
    fadeSpeed[i] = (-20*i)+10;
    letterStep[i] = 30;
  }
}

void SolidFade::randomize(uint8_t ci){
  this -> randomizeColor(ci);
  fadeSpeed[ci] = random(-100,100);
  letterStep[ci] = random(50);
}

void SolidFade::run(Sign &sign, uint8_t ci){
  CHSV clr = color[ci];
  fadeHue[ci] += fadeSpeed[ci];
  uint16_t hue16 = fadeHue[ci];

  for(uint8_t i = 0; i < LETTERS_COUNT; i++){
    clr.hue = (uint8_t)(hue16 >> 8);
    Letter *letter = sign.letters[i];
    letter -> setColor(ci, clr);
    hue16 += letterStep[ci] << 8;
  }
}

bool SolidFade::pushChar(char character, uint8_t ci){
  if( this -> useCharForColor(character, ci)){ return true; };

  int32_t val = 0xFFFF;
  String desc;
  String letter_stp_string = F("Hue Step/Letter");

  switch(character){
    case 'F': val = ++letterStep[ci];
              desc = letter_stp_string; break;
    case 'S': val = --letterStep[ci];
              desc = letter_stp_string; break;
    case 'f': val = this -> incSegSpeed(true, ci);
              desc = FADE_SPEED_STR; break;
    case 's': val = this -> incSegSpeed(false, ci);
              desc = FADE_SPEED_STR; break;
    case 'x': this -> randomize(ci);
              val = color[ci].hue; desc = RANDOM_STR; break;
  }
  return usedSetting(desc, val);

}

void SolidFade::invertColors(){
  Effect::invertColors();
  uint16_t tempHue = fadeHue[0];
  fadeHue[0] = fadeHue[1];
  fadeHue[1] = tempHue;

  uint8_t tempLetterStep = letterStep[0];
  letterStep[0] = letterStep[1];
  letterStep[1] = tempLetterStep;
}

int16_t SolidFade::incSegSpeed(bool isPositive, uint8_t layer){
  if(isPositive){
    fadeSpeed[layer]++;
  }else{
    fadeSpeed[layer]--;
  }
  return fadeSpeed[layer];
}

