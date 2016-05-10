#include "Effect.h"
#include "RandomLetters.h"

RandomLetters::RandomLetters(){
  this -> reset();
}

void RandomLetters::reset(){
}

void RandomLetters::run(Sign &sign, uint8_t layer){

  sign.textChanged = true;
  uint8_t letters_count = sign.letterCount();
  char random_char;

  for(uint8_t i=0; i < letters_count; i++){
    random_char = ' ' + random(95);
    sign.letter(i) -> setChar(random_char);
  }

}

bool RandomLetters::pushChar(char character, uint8_t ci){
  int32_t val = 0xFFFF;
  String desc;

  switch(character){

  }

  return( usedSetting(desc, val) );
}
