#include "SolidColor.h"

SolidColor::SolidColor(){
  this -> reset();
}

void SolidColor::reset(){
  for(uint8_t i=0; i<LAYER_COUNT; i++){
    color[i] = CHSV(128*i,255,255-100*i);
  }
}

void SolidColor::randomize(uint8_t ci){
  this -> randomizeColor(ci);
}

void SolidColor::run(Sign &sign, uint8_t ci){
  uint16_t seg_count = sign.segmentCount();

  bool on = (ci == 0);

  for(uint16_t i=0; i< seg_count; i++){
    Segment currSeg = *sign.segments[i];
    if(currSeg.isOn == on){
      currSeg.setColor(color[ci]);
    }
  }
}

bool SolidColor::pushChar(char character, uint8_t ci){
  if(this -> useCharForColor(character, ci)){return true;};

  int32_t val = 0xFFFF;
  String desc;

  switch(character){
    case 'x':
      this -> randomize(ci);
      val = color[ci].hue; desc = RANDOM_STR; break;
  }
  return( usedSetting(desc, val) );

}
