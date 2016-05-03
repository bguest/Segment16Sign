#include "RandomScroll.h"

RandomScroll::RandomScroll(){
  this -> reset();
}

void RandomScroll::reset(){
}

void RandomScroll::run(Sign &sign, uint8_t layer){

  sign.textChanged = true;
  char random_char = char(' ' + random8(95) );
  sign.pushChar(random_char);
  sign.setCharacters();
}

bool RandomScroll::pushChar(char character, uint8_t ci){
  int32_t val = 0xFFFF;
  String desc;

  switch(character){

  }

  return( usedSetting(desc, val) );
}
