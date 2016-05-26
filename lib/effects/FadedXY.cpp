#include "FadedXY.h"

FadedXY::FadedXY(){
  this -> reset();
}

void FadedXY::reset(){
  for(uint8_t i=0; i<LAYER_COUNT; i++){
    hue[i][0] = 0; hue[i][1] = UINT16_MAX;
    hue[i][2] = 0; hue[i][3] = UINT16_MAX;
  }
}

void FadedXY::run(Sign &sign, uint8_t ci){

  uint8_t seg_count = sign.segmentCount();
  bool on = (ci == 0);

  for(uint8_t i=0; i<seg_count; i++){
    Segment *curr_seg = sign.segments[i];
    if(curr_seg->isOn == on){
      uint8_t pixel_count = curr_seg->pixelCount();
      for(uint8_t j=0; j<pixel_count; j++){
        Pixel *pixel = curr_seg->pixels[j];
        this->interpolate(*pixel, ci);
      }
    }

  }

}

void FadedXY::interpolate(Pixel &pixel, uint8_t ci){
  uint8_t maxX = LETTERS_COUNT * LETTER_PIXEL_WIDTH;

  uint8_t c0 = hue[ci][0] >> 8;
  uint8_t c1 = hue[ci][1] >> 8;

  uint8_t h;
  uint16_t x = pixel.x();
  h = c0 + x*(c1-c0)/maxX;

  pixel.setColor( CHSV(h,255,255));
}
