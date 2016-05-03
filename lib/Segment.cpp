#include "Segment.h"

Segment::Segment(){
}

Segment::Segment(uint8_t length){
  //pixels[length] = new Pixel[length];

  for(uint8_t i=0; i< length; i++){
    pixels[i] = new Pixel();
  }
  _length = length;

  isOn = false;
};

uint16_t Segment::pixelCount(){
  return _length;
}

void Segment::toArray(CRGB array[], uint16_t &currIdx){

  for(uint8_t i=0; i< _length; i++){
    array[currIdx] = pixels[i] -> getColor();
    currIdx++;
  }
}

void Segment::setColor(uint8_t layer, CHSV color){
  bool on = (layer == 0);
  if(isOn == on){
    this -> setColor(color);
  }
}

void Segment::setColor(CHSV color){
  for(uint8_t i=0; i< _length; i++){
    pixels[i] -> setColor(color);
 }
}

CHSV16 Segment::getHsv16(){
  return pixels[0] -> getHsv16();
}

void Segment::setHsv16(uint8_t layer, CHSV16 color){
  bool on = (layer == 0);
  if(isOn == on){
    this -> setHsv16(color);
  }
}

void Segment::setHsv16(CHSV16 color){
  for(uint8_t i=0; i< _length; i++){
    pixels[i] -> setHsv16(color);
 }
}

char Segment::orientation(){
  switch(index){
    case 0: case 1:
    case 14: case 15:
    case 5: case 4:
      return HORIZONTAL;

    case 7: case 6:
    case 11: case 10:
    case 2: case 3:
      return VERTICAL;

    case 8: case 9:
      return DIAGONAL_LEFT;

    case 12: case 13:
      return DIAGONAL_RIGHT;

  }
  return HORIZONTAL;
}
