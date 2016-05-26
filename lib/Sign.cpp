#include "Sign.h"

Sign::Sign(){}

void Sign::init(){

  uint8_t lengths[LETTERS_COUNT][16] = {
    {2, 2, 4, 4, 2, 2, 4, 4, 2, 2, 4, 4, 2, 2, 2, 2},
    {2, 2, 4, 4, 2, 2, 4, 4, 2, 2, 4, 4, 2, 2, 2, 2},
    {2, 2, 4, 4, 2, 2, 4, 4, 2, 2, 4, 4, 2, 2, 2, 2},
    {2, 2, 4, 4, 2, 2, 4, 4, 2, 2, 4, 4, 2, 2, 2, 2}
  };

  for(uint16_t i=0; i < LETTERS_COUNT; i++){
    letters[i].init(0, lengths[i]);
    for(uint16_t j=0; j<16; j++){
      segments[(i*16)+j] = letters[i].segment(j);
    }
  }
  //uint16_t pixel_count = this -> pixelCount();

  characters[0] = 'D';
  characters[1] = 'A';
  characters[2] = 'D';
  characters[3] = 'A';
};

void Sign::pushChar(char character){
  this -> pushChar(character, false);
}
void Sign::pushChar(char character, bool shouldPrint){
  if( shouldPrint ){
    Serial.print(character);
    Serial1.print(character);
  }
  if( binarySegsForChar(character) == 0xFFFF ){ return; }

  for(uint8_t i=0; i< LETTERS_COUNT - 1; i++){
    characters[i] = characters[i+1];
  }
  characters[LETTERS_COUNT-1] = character;

  this -> sanitize();

  for(uint8_t i=0; i< LETTERS_COUNT; i++){
    letters[i].currentChar = characters[i];
  }
}

Letter* Sign::letter(uint8_t i){
  return &letters[i];
}

void Sign::setCharacters(){
  for(uint8_t i=0; i<LETTERS_COUNT; i++){
    letters[i].setChar(characters[i]);
  }
}

void Sign::setLayer(uint8_t layer, bool isOn){
  for(uint8_t i=0; i<LETTERS_COUNT; i++){
    letters[i].setLayer(layer, isOn);
  }
}

void Sign::setWord(String word){
  uint8_t size = min((uint8_t)word.length(), LETTERS_COUNT);

  for(uint8_t i=0; i<size; i++){
    characters[i] = word.charAt(i);
  }
  this -> sanitize();

  for(uint8_t i=0; i<size; i++){
    letters[i].setChar( characters[i] );
  }
}

void Sign::_setWord(String word, uint8_t size){
  char ctr;
  for(uint8_t i=0; i< size; i++){
    ctr = word.charAt(i);
    characters[i] = ctr;
    letters[i].setChar( ctr );
  }
}

#define BAD_WORDS_COUNT 16
const String badWords[BAD_WORDS_COUNT] = {
  //"TEST"
  "CUNT", "GOOK", "FAGG",
  "FAG ", " FAG", "COON", "HEEB", "SLUT",
  "COON", "KKK ", " KKK", "KYKE", "SPIC",
  "SPIK", "TWAT", "HOMO"
};

void Sign::sanitize(){
  String ctrs = String(characters).substring(0, LETTERS_COUNT);
  String badWord;
  for(uint8_t i=0; i< BAD_WORDS_COUNT; i++){
    badWord = badWords[i];
    if(badWord.equalsIgnoreCase(ctrs)){
      this -> _setWord(String("LOVE"), LETTERS_COUNT);
    }
  }
}

uint16_t Sign::pixelCount(){

  if(_pixel_count > 0){
    return _pixel_count;
  }

  uint16_t pixel_count = 0;
  for(uint8_t i = 0; i < LETTERS_COUNT; i++){
    pixel_count += letters[i].pixelCount();
  }
  _pixel_count = pixel_count;
  return pixel_count;
}

uint8_t Sign::letterCount(){
  return LETTERS_COUNT;
}

uint16_t Sign::segmentCount(){
  return 16*LETTERS_COUNT;
}
