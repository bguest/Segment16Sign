#include "Effect.h"
#include "BasicTyping.h"

BasicTyping::BasicTyping(){
}

void BasicTyping::run(Sign &sign, uint8_t layer){
  uint8_t letters_count = sign.letterCount();

  // Set Characters
  for(uint8_t i=0; i < letters_count; i++){
    char current_char = sign.characters[i];
    sign.letter(i) -> setChar(current_char);
  }

}
