
#include "Segment16.h"

#define DATA_PIN 11
#define CLOCK_PIN 13

Segment16::Segment16(void){
  isInsertMode = false;
};

void Segment16::init(){

  Serial.begin(9600);
  Serial1.begin(9600);

  String prompt = "Type any character to start";
  Serial.println(prompt);
  Serial1.println(prompt);

  Serial1.println("WOOT");
  delay(500);  // Catch Due reset problem

  keyboard.init();
  sign.init();

  uint16_t pixel_count = sign.pixelCount();
  FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, pixel_count);
}

void Segment16::run(){
  keyboard.run();
  if(keyboard.isAvailable){
    this->pushChar(keyboard.data);
  }
  this->show();
  delay(5);
}

void Segment16::pushChar(uint32_t character){
  if( this -> decideInput(character) ){ return; } // Don't push character if its an insert key

  if(isInsertMode){
    if(!effects.pushInsert(character)){
      sign.pushChar( (char)character, true);
      effects.signWasUpdated(sign);
    }
  }else{
    effects.pushChar(character);
  }
}

void Segment16::show(){

  effects.run(sign);

  uint16_t currentPixel = 0;
  for(uint8_t i=0; i < LETTERS_COUNT; i++){
    sign.letter(i) -> toArray(leds, currentPixel);
  }
  FastLED.show();
};

bool Segment16::decideInput(char newInput){
  for(uint8_t i=0; i< SAVED_INPUT_COUNT-1; i++){
    input[i] = input[i+1];
  }
  input[SAVED_INPUT_COUNT-1] = newInput;

  bool esc = newInput == 0x1B || (input[0] == 'k' && input[1] == 'j');
  if(isInsertMode && esc ){
    Serial1.print("\nNormal Mode");
    isInsertMode = false;
  }else if(!isInsertMode && (newInput == 'i' || newInput == ' ')){
    Serial1.print("\nInsert Mode\n");
    isInsertMode = true;
    return true;
  }
  return false;
}
