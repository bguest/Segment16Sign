#include "FadedXY.h"

FadedXY::FadedXY(){
  this -> reset();
}

void FadedXY::reset(){
  for(uint8_t i=0; i<LAYER_COUNT; i++){
    color[i] = CHSV(128*i,255,255);

    hue[i][0] = 0; hue[i][1] = UINT16_MAX/2-1;
    hue[i][2] = UINT16_MAX/2-1; hue[i][3] = UINT16_MAX-1;
    hueOffset[i] = 1;
    hueOffsetSpeed[i] = random(-20, 20);
    for(uint8_t j=0; j<FADED_XY_POINT_COUNT; j++){
      hueSpeed[i][j] = 0;
    }
  }
}

void FadedXY::randomize(uint8_t ci){
  hueOffsetSpeed[ci] = random(-50,50);
  for(uint8_t i = 0; i<FADED_XY_POINT_COUNT; i++){
    hue[ci][i] = random(0, UINT16_MAX);
    hueSpeed[ci][i] = random(-100, 100);
  }
}

void FadedXY::invertColors(){
  Effect::invertColors();
  for(uint8_t i=0; i<FADED_XY_POINT_COUNT; i++){
    uint16_t tempHue = hue[0][i];
    hue[0][i] = hue[1][i];
    hue[1][i] = tempHue;
  }
}

void FadedXY::run(Sign &sign, EffectData &data, uint8_t ci){

  hueOffset[ci] += hueOffsetSpeed[ci];

  for(uint8_t i=0; i<FADED_XY_POINT_COUNT; i++){
    hue[ci][i] += hueSpeed[ci][i];
  }

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

bool FadedXY::pushChar(char character, uint8_t ci){
  if( this -> useCharForColor(character, ci)){ return true; };

  int32_t val = 0xFFFF;
  String desc;

  switch(character){
    case 'q': val = (hue[ci][0] += HUE_STEP << 8);
              desc = "0:" + HUE_STR; break;
    case 'Q': val = (hue[ci][0] -= HUE_STEP << 8);
              desc = "0:" + HUE_STR; break;

    case 'w': val = (hue[ci][1] += HUE_STEP << 8);
              desc = "1:" + HUE_STR; break;
    case 'W': val = (hue[ci][1] -= HUE_STEP << 8);
              desc = "1:" + HUE_STR; break;

    case 'e': val = (hue[ci][2] += HUE_STEP << 8);
              desc = "2:" + HUE_STR; break;
    case 'E': val = (hue[ci][2] -= HUE_STEP << 8);
              desc = "2:" + HUE_STR; break;

    case 'r': val = (hue[ci][3] += HUE_STEP << 8);
              desc = "3:" + HUE_STR; break;
    case 'R': val = (hue[ci][3] -= HUE_STEP << 8);
              desc = "3:" + HUE_STR; break;

    case 'f': val = (hueOffsetSpeed[ci] += 1);
              desc = FADE_SPEED_STR; break;

    case 's': val = (hueOffsetSpeed[ci] -= 1);
              desc = FADE_SPEED_STR; break;

    case 'x': this -> randomize(ci);
              val = hueOffsetSpeed[ci];
              desc = RANDOM_STR; break;

  }

  return( usedSetting(desc, val) );

}

void FadedXY::interpolate(Pixel &pixel, uint8_t ci){
  uint16_t maxX = LETTERS_COUNT * LETTER_PIXEL_WIDTH << 8;
  uint16_t maxY = 11 << 8;

  uint16_t c0 = hue[ci][0];
  uint16_t c1 = hue[ci][1];
  uint16_t c2 = hue[ci][2];
  uint16_t c3 = hue[ci][3];

  uint16_t h, h0, h1;
  uint32_t x = pixel.x() << 8;
  h0 = c0 + x*(c1-c0)/maxX;
  h1 = c2 + x*(c3-c2)/maxX;

  uint32_t y = pixel.y() << 8;
  h = h0 + y*(h1-h0)/maxY + hueOffset[ci];

  pixel.setHsv16( CHSV16(h, color[ci].s << 8, color[ci].v << 8) );
}

