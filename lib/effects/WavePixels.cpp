
#include "WavePixels.h"

WavePixels::WavePixels(){
  this -> reset();
}

void WavePixels::reset(){
  for(uint8_t i=0; i< LAYER_COUNT; i++){
    color[i] = CHSV(128, 255, 255);
    cycleTime[i] = 2500;
    hueA[i] = INT16_MAX/2;
  }
}

void WavePixels::randomize(uint8_t ci){
  this -> randomizeColor(ci);
  cycleTime[ci] = random16(200,10000);
  hueA[ci] = random16(INT16_MAX);
}

void WavePixels::run(Sign &sign, EffectData &data, uint8_t ci){
  uint16_t angle = (millis() % cycleTime[ci])*UINT16_MAX/cycleTime[ci];

  int16_t delta_hue = hueA[ci] * sin16(angle)/UINT16_MAX;
  uint16_t seg_count = sign.segmentCount();

  bool on = (ci == 0);

  for(uint8_t i=0; i < seg_count; i++){
    Segment *curr_seg = sign.segments[i];

    if(curr_seg -> isOn == on){
      curr_seg -> setColor(color[ci]);
      delta_hue = -delta_hue;
      int16_t hue_add = delta_hue;

      uint8_t pixel_count = curr_seg -> pixelCount();

      for(uint8_t j = 0; j < pixel_count; j++ ){
        Pixel *currPixel = curr_seg -> pixels[j];
        currPixel -> addHue16(hue_add);
        hue_add += delta_hue;
      }
    }
  }

}


bool WavePixels::pushChar(char character, uint8_t ci){
  if( this -> useCharForColor(character, ci)){ return true; };

  int32_t val = 0xFFFF;
  String desc;

  const uint16_t ampStep = 200;
  const uint8_t cycleStep = 10;

  switch(character){
    case 'e': val = (hueA[ci] += ampStep);
              desc = HUE_AMP_STR; break;
    case 'E': val = (hueA[ci] -= ampStep);
              desc = HUE_AMP_STR; break;
    case 'f': val = (cycleTime[ci] -= cycleStep);
              desc = FADE_SPEED_STR; break;
    case 's': val = (cycleTime[ci] += cycleStep);
              desc = FADE_SPEED_STR; break;
  }

  return( usedSetting(desc, val) );
}

void WavePixels::invertColors(){
  Effect::invertColors();

  uint16_t tempCycle = cycleTime[0];
  cycleTime[0] = cycleTime[1];
  cycleTime[1] = tempCycle;

  int16_t tempHueA = hueA[0];
  hueA[0] = hueA[1];
  hueA[1] = tempHueA;
}
