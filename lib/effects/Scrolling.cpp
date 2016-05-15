#include "Scrolling.h"

Scrolling::Scrolling(){
  this -> reset();
}

void Scrolling::reset(){
  numBeats = 2;
  beatIdx = 0;
  this -> softReset();
}

void Scrolling::randomize(uint8_t ci){
  numBeats = random(0,10);
}

void Scrolling::softReset(){
  charCount = 0;

  for(uint8_t j=0; j<SCROLL_LENGTH; j++){
    buffer[j] = ' ';
  }
}

void Scrolling::pushToBuffer(char character){

  if(charCount == SCROLL_LENGTH){
    this->shiftLeft();
  }else{
    charCount++;
  }

  buffer[charCount-1] = character;
}

void Scrolling::shiftLeft(){
  for(uint8_t i=0; i<SCROLL_LENGTH-1; i++){
    buffer[i] = buffer[i+1];
  }
}

void Scrolling::backspaceBuffer(){
  charCount--;
}

bool Scrolling::pushInsert(char chtr){
  if(chtr == 13 || chtr == '\n' ){
    beatIdx = 0;
    charCount = 0;
  }else if(chtr == 127){
    this -> backspaceBuffer();
  }else{
    this -> pushToBuffer(chtr);
  }
  Serial1.print(chtr);
  Serial.print(chtr);
  return true;
}

bool Scrolling::pushChar(char character, uint8_t ci){
  int32_t val = 0xFFFF;
  String desc;

  switch(character){
    case 'u': this -> softReset(); val=1;
      desc = RESET_STR; break;
    case 'K': val = ++numBeats;
      desc = STEP_SIZE_STR; break;
    case 'J': val = --numBeats;
      desc = STEP_SIZE_STR; break;
    case '/': this -> randomize(ci);
      val = numBeats;
      desc = RANDOM_STR; break;
  }

  return( usedSetting(desc, val) );
}

void Scrolling::run(Sign &sign, uint8_t layer){
  if(beatIdx++ % numBeats > 0){ return;}

  sign.textChanged = true;

  char word[4];
  for(uint8_t i=0; i< LETTERS_COUNT; i++){
    uint8_t idx = (beatIdx+i) % charCount;
    word[i] = buffer[idx];
  }

  sign.setWord( String( word ) );
}
