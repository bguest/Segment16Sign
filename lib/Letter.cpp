#include "Letter.h"

Letter::Letter(){};

void Letter::init(uint8_t idx, uint8_t lengths[16]){

  uint8_t start = 0;
  uint8_t endPlus1;

  for(uint8_t i=0; i<16; i++){
    endPlus1 = start+lengths[i];
    segments[i].init(pixels, start, endPlus1);
    segments[i].index = i;
    start = endPlus1;
  }

  letterIdx = idx;
  this->setPixelLocations();

};

void Letter::setPixelLocations(){

  uint8_t xy[2*NUM_2_PIXEL+4*NUM_4_PIXEL][2] = {
    {1,0}, {2,0},                // 0
    {4,0}, {5,0},                // 1
    {6,1}, {6,2}, {6,3}, {6,4},  // 2
    {6,6}, {6,7}, {6,8}, {6,9},  // 3
    {5,10},{4,10},               // 4
    {2,10},{1,10},               // 5
    {0,9}, {0,8}, {0,7}, {0,6},  // 6
    {0,4}, {0,3}, {0,2}, {0,1},  // 7
    {1,2}, {2,3},                // 8
    {4,7}, {5,6},                // 9
    {3,9}, {3,8}, {3,7}, {3,6},  // 10
    {3,4}, {3,3}, {3,2}, {3,1},  // 11
    {5,2}, {4,3},                // 12
    {2,7}, {2,8},                // 13
    {1,5}, {2,5},                // 14
    {4,5}, {5,5}                 // 15
  };

  uint8_t pixelCount = this->pixelCount();
  uint8_t offset = LETTER_PIXEL_WIDTH * letterIdx;

  for(uint8_t i=0; i<pixelCount; i++){
    pixels[i].setXY( xy[i][0] + offset, xy[i][1] );
  }

}

uint16_t Letter::pixelCount(){
  /*
  uint16_t pixel_count = 0;
  for(uint8_t i=0; i < 16; i++){
    pixel_count += segments[i].pixelCount();
  }
  return pixel_count;
  */
  return 2*NUM_2_PIXEL+4*NUM_4_PIXEL;
}

Segment* Letter::segment(uint8_t i){
  return &segments[i];
}

Pixel* Letter::pixel(uint8_t i){
  return &pixels[i];
}

void Letter::setChar(char character){
  currentChar = character;
  uint16_t binarySegs = binarySegsForChar(character);
                  //0123456789012345
  uint16_t mask = 0b1000000000000000;
  for(uint8_t i=0; i<16; i++){
    if(mask & binarySegs){
      segments[i].isOn = true;
    }else{
      segments[i].isOn = false;
    }
    mask = mask >> 1;
  }

}
void Letter::setLayer(uint8_t layer, bool isOn){
  uint16_t binarySegs = binarySegsForChar(currentChar);
  if(layer == 1){ binarySegs = ~binarySegs;}
                  //0123456789012345
  uint16_t mask = 0b1000000000000000;
  for(uint8_t i=0; i<16; i++){
    if(mask & binarySegs){
      segments[i].isOn = isOn;
    }
    mask = mask >> 1;
  }
}

void Letter::setColor(uint8_t layer, CHSV color){
  bool on = (layer == 0);
  for(uint8_t i=0; i<16; i++){
    Segment curr_seg = segments[i];
    if(curr_seg.isOn == on){
      curr_seg.setColor(color);
    }
  }
}

CHSV16 Letter::getHsv16(uint8_t layer){
  bool on = (layer == 0);
  for(uint8_t i=0; i<16; i++){
    Segment curr_seg = segments[i];
    if(curr_seg.isOn == on){
      return curr_seg.getHsv16();
    }
  }
  return segments[0].getHsv16();
}

void Letter::setHsv16(uint8_t layer, CHSV16 color){
  for(uint8_t i=0; i<16; i++){
    Segment curr_seg = segments[i];
    curr_seg.setHsv16(layer, color);
  }
}

void Letter::toArray(CRGB array[], uint16_t &currIdx){
  for(uint16_t i=0; i<16; i++){
    segments[i].toArray(array, currIdx);
  }

}

