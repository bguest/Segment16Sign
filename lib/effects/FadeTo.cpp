#include "FadeTo.h"

FadeTo::FadeTo(){
  this -> reset();
}

void FadeTo::reset(){
  for(uint8_t i=0; i<LAYER_COUNT; i++){
    this -> randomizeColor(i);
  }
  fadeTime = 500;
  for(uint8_t i=0; i<16*LETTERS_COUNT; i++){
    segHue[i] = color[0].hue << 8;
  }
}

void FadeTo::randomize(uint8_t ci){
  this -> randomizeColor(ci);
  fadeTime = random(10,1000);
  for(uint8_t i=0; i<16*LETTERS_COUNT; i++){
    segHue[i] = color[ci].hue << 8;
  }
}

void FadeTo::run(Sign &sign, uint8_t ci){
  bool on = (ci == 0);
  uint16_t seg_count = sign.segmentCount();
  CHSV clr = color[ci];
  uint16_t seg_speed;
  uint16_t hue_final = (uint16_t)(color[ci].hue << 8);
  CHSV16 seg_color;

  for(uint8_t i=0; i< seg_count; i++){
    Segment currSeg = *sign.segments[i];
    if(currSeg.isOn == on){
      seg_color = currSeg.getHsv16();
      seg_speed = (hue_final - seg_color.hue)/fadeTime;
      seg_color.hue += seg_speed;
      seg_color.sat = clr.sat << 8;
      seg_color.val = clr.val << 8;
      currSeg.setHsv16(seg_color);
    }

  }
}

bool FadeTo::pushChar(char character, uint8_t ci){
  if( this -> useCharForColor(character, ci)){ return true; };

  int32_t val = 0xFFFF;
  String desc;

  switch(character){
    case 's': val = (fadeTime += FADE_TIME_STEP);
              desc = CONVERGE_TIME_STR; break;
    case 'f': val = (fadeTime -= FADE_TIME_STEP);
              desc = CONVERGE_TIME_STR; break;
    case 'x': this -> randomize(ci);
              val = segHue[ci];
              desc = RANDOM_STR; break;
  }
  return( usedSetting(desc, val) );
}
