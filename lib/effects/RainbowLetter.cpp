#include "Effect.h"
#include "RainbowLetter.h"

RainbowLetter::RainbowLetter(){
  this -> reset();
}

void RainbowLetter::reset(){
  isStatic = true;
  changeOnBeat = true;
  for(uint8_t i=0; i<LAYER_COUNT; i++){
    color[i] = CHSV(128*i,255,255);
    hueStep[i] = 40;
    cycleTime[i] = 2500;
    hueA[i] = INT16_MAX/8;
  }
}

void RainbowLetter::randomize(uint8_t ci){
  this -> randomizeColor(ci);
  isStatic = (bool)random8(0,1);
  changeOnBeat = true;
  hueStep[ci] = random8(-120,120);
  cycleTime[ci] = random16(200,4000);
  hueA[ci] = random16(INT16_MAX/2);
}

void RainbowLetter::run(Sign &sign, EffectData &data, uint8_t ci){
  if( sign.textChanged ){ this -> signWasUpdated(sign, ci);}

  uint8_t letters_count = sign.letterCount();
  CHSV16 curr_color = CHSV16(color[ci]);

  if(changeOnBeat && sign.onBeat){
    color[ci].hue += hueStep[ci];
  }

  uint16_t angle = (millis() % cycleTime[ci])*UINT16_MAX/cycleTime[ci];
  int16_t delta_hue = hueA[ci] * sin16(angle)/UINT16_MAX;

  uint16_t hueStep16 = hueStep[ci] << 8;
  CHSV16 wave_color;

  for(uint8_t i=0; i<letters_count; i++){
    Letter* curr_letter = sign.letter(i);
    wave_color = curr_color;
    delta_hue = -delta_hue;
    wave_color.hue += delta_hue;
    curr_letter -> setHsv16(ci, wave_color);
    curr_color.hue += hueStep16;
  }

}

bool RainbowLetter::pushChar(char character, uint8_t ci){
  if( this -> useCharForColor(character, ci)){ return true; };

  int32_t val = 0xFFFF;
  String desc;

  const uint16_t ampStep = 200;
  const uint8_t cycleStep = 20;

  switch(character){

    case 'w': val = (color[ci].hue += hueStep[ci]);
              desc = "Jump forward"; break;
    case 'W': val = (color[ci].hue -= hueStep[ci]);
              desc = "Jump backward"; break;

    case 'e': val = (hueA[ci] += ampStep);
              desc = HUE_AMP_STR; break;
    case 'E': val = (hueA[ci] -= ampStep);
              desc = HUE_AMP_STR; break;

    case 'f': val = (cycleTime[ci] -= cycleStep);
              desc = FADE_SPEED_STR; break;
    case 's': val = (cycleTime[ci] += cycleStep);
              desc = FADE_SPEED_STR; break;

    case 'S': val = (hueStep[ci] -= HUE_STEP);
              desc = STEP_SIZE_STR; break;
    case 'F': val = (hueStep[ci] += HUE_STEP);
              desc = STEP_SIZE_STR; break;

    case 'd': val = (isStatic = !isStatic);
              desc = F("Static"); break;
    case 'D': val = (changeOnBeat = !changeOnBeat);
              desc = ON_BEAT_STR; break;

    case 'x': this -> randomize(ci);
              val = hueStep[ci];
              desc = RANDOM_STR; break;
  }
  return( usedSetting(desc, val));
}

void RainbowLetter::signWasUpdated(Sign &sign, uint8_t layer){
  if(isStatic){return;}
  color[layer].hue += hueStep[layer];
}

void RainbowLetter::signWasUpdated(Sign &sign){
  for(uint8_t i=0; i< LAYER_COUNT; i++){
    this -> signWasUpdated(sign, i);
  }
}
