
#include "Effect.h"

//const String HueStrng = "Hue:";

Effect::Effect(){
}

void Effect::reset(){
}
void Effect::run(Sign &sign, EffectData &data, uint8_t layer){
}
void Effect::signWasUpdated(Sign &sign){
}
bool Effect::pushInsert(char character){
  return false;
}
bool Effect::pushChar(char character, uint8_t layer){
  return false;
}
void Effect::randomize(uint8_t layer){
}

void Effect::randomizeColor(uint8_t ci){
  color[ci].hue = random(0, UINT8_MAX);

  if(ci == BACKGROUND_LAYER){
    color[ci].value = random(0, UINT8_MAX/2);
  }else{
    color[ci].value = random(UINT8_MAX/2, UINT8_MAX);
  }
  color[ci].saturation = random(20) == 20 ? 0 : UINT8_MAX;
}


bool Effect::useCharForColor(char character, uint8_t ci){
  int32_t val = 0xFFFF;
  String desc;

  switch(character){
    case '0': val = color[ci].value = 0;
              desc = VAL_STR; break;
    case '9': val = color[ci].value = 255;
              desc = VAL_STR; break;
    case 'c': val = (color[ci].hue += HUE_STEP);
              desc = HUE_STR; break;
    case 'C': val = (color[ci].hue -= HUE_STEP);
              desc = HUE_STR; break;
    case 'v': val = (color[ci].saturation += VALUE_STEP);
              desc = SAT_STR; break;
    case 'V': val = (color[ci].saturation -= VALUE_STEP);
              desc = SAT_STR; break;
    case 'B': val = (color[ci].value -= VALUE_STEP);
              desc = VAL_STR; break;
    case 'b': val = (color[ci].value += VALUE_STEP);
              desc = VAL_STR; break;
  }
  return( usedSetting(desc, val) );
}

void Effect::invertColors(){
  CHSV tempColor = color[0];
  color[0] = color[1];
  color[1] = tempColor;
}

void Effect::off(Sign &sign){
  uint16_t seg_count = sign.segmentCount();
  for(uint16_t i=0; i<seg_count; i++){
    sign.segments[i] -> isOn = false;
  }
}

