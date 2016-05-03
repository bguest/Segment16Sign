#include "WordsEnter.h"

WordsEnter::WordsEnter(){
  this -> reset();
}

void WordsEnter::reset(){
  numBeats = 5;
  beatIdx = 0;
  this -> softReset();
}

void WordsEnter::randomize(uint8_t ci){
  numBeats = random(0,10);
}

void WordsEnter::softReset(){
  wordIdx = 0;
  wordsCount = 0;
  letterIdx = 0;

  for(uint8_t j=0; j<LETTERS_COUNT; j++){
    buffer[j] = ' ';
    for(uint8_t i=0; i<WORDS_COUNT; i++){
      words[i][j] = ' ';
    }
  }
}

void WordsEnter::pushBuffer(){
  for(uint8_t i=0; i<LETTERS_COUNT; i++){
    words[wordIdx][i] = buffer[i];
    buffer[i] = ' ';
  }
}
void WordsEnter::pushToBuffer(char character){
  for(uint8_t i=0; i< LETTERS_COUNT - 1; i++){
    buffer[i] = buffer[i+1];
  }
  buffer[LETTERS_COUNT-1] = character;
}

void WordsEnter::backspaceBuffer(){
  for(uint8_t i=LETTERS_COUNT; i>0 ;  i--){
    buffer[i] = buffer[i-1];
  }
  buffer[0] = ' ';
}

bool WordsEnter::pushInsert(char chtr){
  if(chtr == 13 || chtr == '\n' ){
    beatIdx = 0;
    wordsCount++;
    wordsCount = wordsCount % WORDS_COUNT;
    wordIdx = wordsCount-1;
    this -> pushBuffer();
  }else if(chtr == 127){
    this -> backspaceBuffer();
  }else{
    this -> pushToBuffer(chtr);
  }
  Serial1.print(chtr);
  Serial.print(chtr);
  return true;
}

bool WordsEnter::pushChar(char character, uint8_t ci){
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

void WordsEnter::run(Sign &sign, uint8_t layer){
  if(beatIdx++ % numBeats > 0){ return;}

  sign.textChanged = true;

  sign.setWord( String( words[wordIdx] ) );
  wordIdx++;
  wordIdx = wordIdx % wordsCount;
}
