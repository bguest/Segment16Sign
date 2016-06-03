#include "LinesOn.h"

LinesOn::LinesOn(){
  this -> reset();
}

void LinesOn::reset(){
  changeOnBeat = true;
  orientation = HORIZONTAL;
}

void LinesOn::randomize(uint8_t ci){
  changeOnBeat = true;
  orientation = random8(ORIENTATION_COUNT - 1);
}

void LinesOn::run(Sign &sign, EffectData &data, uint8_t layer){
  uint8_t seg_count = sign.segmentCount();

  if(changeOnBeat && sign.onBeat){
    sign.textChanged = true;
    this -> incOrient();
  }

  this -> off(sign);
  for(uint8_t i=0; i<seg_count; i++){
    Segment *curr_seg = sign.segments[i];
    if(curr_seg -> orientation() == orientation){
      sign.segments[i] -> isOn = true;
    }
  }
}

void LinesOn::incOrient(){
  orientation++;
  orientation %= ORIENTATION_COUNT;
}

bool LinesOn::pushChar(char character, uint8_t ci){
  int32_t val = 0xFFFF;
  String desc;

  switch(character){
    case ']': this -> incOrient();
              val = orientation;
              desc = ORIENT_STR; break;
    case '[': orientation--;
              val = orientation %= ORIENTATION_COUNT;
              desc = ORIENT_STR; break;
    case '/': this -> randomize(ci);
              val = orientation;
              desc = RANDOM_STR; break;
    case 'p': val = (changeOnBeat = !changeOnBeat);
              desc = ON_BEAT_STR; break;
  }
  return( usedSetting(desc, val) );
}

