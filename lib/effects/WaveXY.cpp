#include "WaveXY.h"

WaveXY::WaveXY(){
  this -> reset();
}

void WaveXY::reset(){
  isWaveValue = true;
  for(uint8_t ci=0; ci<LAYER_COUNT; ci++){
    color[ci] = CHSV(128*ci,255,255);
  }

  for(uint8_t i=0; i<2; i++){
    for(uint8_t j=0; j<LAYER_COUNT; j++){
      freq[i][j] = UINT8_MAX/2;
      step[i][j] = 0;
      offset[i][j] = 0;
    }
  }
}

void WaveXY::randomize(uint8_t ci){
}

void WaveXY::invertColors(){
  Effect::invertColors();
}

void WaveXY::run(Sign &sign, EffectData &data, uint8_t ci){

  uint8_t seg_count = sign.segmentCount();
  bool on = (ci == 0);

  uint8_t i;

  for(i=0; i<2; i++){
    offset[i][ci] += step[i][ci];
  }

  for(i=0; i<seg_count; i++){
    Segment *curr_seg = sign.segments[i];
    if(curr_seg->isOn == on){
      uint8_t pixel_count = curr_seg->pixelCount();
      for(uint8_t j=0; j<pixel_count; j++){
        Pixel *pixel = curr_seg->pixels[j];
        this->calculate(*pixel, ci);
      }

    }
  }

}

void WaveXY::calculate(Pixel &pixel, uint8_t ci){
  uint16_t max[2];
  max[0] = LETTERS_COUNT * LETTER_PIXEL_WIDTH << 8;
  max[1] = 11 << 8;

  uint32_t u[2];
  u[0] = pixel.x() << 8;
  u[1] = pixel.y() << 8;

  const uint16_t N[2] = {2, 1};

  uint16_t B[2];
  int16_t h = 0;

  for(uint8_t i=0; i<2; i++){
    B[i] = freq[i][ci];
    h += sin16( u[i]*UINT16_MAX/max[i]*B[i]*N[i]/UINT8_MAX + offset[i][ci])/2;
  }

  uint16_t hue = h + (color[ci].h << 8);
  uint16_t val = isWaveValue ? h + INT16_MAX : color[ci].v << 8;

  pixel.setHsv16( CHSV16(hue, color[ci].s << 8, val) );
}

bool WaveXY::pushChar(char character, uint8_t ci){
  if( this -> useCharForColor(character, ci)){ return true; };

  int32_t val = 0xFFFF;
  String desc;

  switch(character){
    case 'q': val = ++freq[0][ci];
              desc = X_STR + HUE_PERIOD_STR; break;
    case 'Q': val = --freq[0][ci];
              desc = X_STR + HUE_PERIOD_STR; break;

    case 'w': val = ++freq[1][ci];
              desc = Y_STR + HUE_PERIOD_STR; break;
    case 'W': val = --freq[1][ci];
              desc = Y_STR + HUE_PERIOD_STR; break;

    case 'f': val = ++step[0][ci];
              desc = X_STR + FADE_SPEED_STR; break;
    case 's': val = --step[0][ci];
              desc = X_STR + FADE_SPEED_STR; break;

    case 'F': val = ++step[1][ci];
              desc = Y_STR + FADE_SPEED_STR; break;
    case 'S': val = --step[1][ci];
              desc = Y_STR + FADE_SPEED_STR; break;

    case 'd': val = isWaveValue = !isWaveValue;
              desc = VAL_STR; break;
    case 'z': this -> reset();
              desc = RESET_STR; break;
    case 'x': this -> randomize(ci);
              desc = RANDOM_STR; break;
  }

  return( usedSetting(desc, val) );

}
