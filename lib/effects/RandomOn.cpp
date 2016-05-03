#include "Effect.h"
#include "RandomOn.h"

RandomOn::RandomOn(){
  this -> reset();
}

void RandomOn::reset(){
  onCount = 1;
  shouldReset = true;
  turnOn = true;
}

void RandomOn::randomize(uint8_t ci){
  onCount = random(20);
  shouldReset = true;
  turnOn = true;
}

void RandomOn::run(Sign &sign, uint8_t layer){
  sign.textChanged = true;

  uint16_t seg_count = sign.segmentCount();
  if(shouldReset){
    this -> off(sign);
    shouldReset = false;
  }else{
    sign.setLayer(BACKGROUND_LAYER, false);
  }
  for(uint8_t i = 0; i < onCount; i++){
    uint8_t rand = random8(0,seg_count);
    sign.segments[rand] -> isOn = turnOn;
  }
}

bool RandomOn::pushChar(char character, uint8_t ci){
  int32_t val = 0xFFFF;
  String desc;

  switch(character){
    case 'o': val = (turnOn = !turnOn);
              desc = SET_SEGS_STR; break;
    case 'u': shouldReset = true; val = 1;
              desc = RESET_STR; break;

    case ']': val = (++onCount);
              desc = NUMBER_ON_STR; break;
    case '[': val = (--onCount);
              desc = NUMBER_ON_STR; break;
    case '/': this -> randomize(ci);
              val = onCount;
              desc = RANDOM_STR; break;
  }
  return( usedSetting(desc, val) );
}
