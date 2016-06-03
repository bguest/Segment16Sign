#include "Effect.h"
#include "RainbowSegment.h"

RainbowSegment::RainbowSegment(){
  this -> reset();
}

void RainbowSegment::reset(){
  isStatic = true;
  changeOnBeat = true;
  for(uint8_t i=0; i<LAYER_COUNT; i++){
    color[i] = CHSV(128*i,255,255);
    hueStep[i] = 5;
    beatStep[i] = 35;
  }
}

void RainbowSegment::randomize(uint8_t ci){
  isStatic = (bool)random8(0,1);
  changeOnBeat = true;
  this -> randomizeColor(ci);
  hueStep[ci] = random8(-20,20);
  beatStep[ci] = random8(-120,120);
}

void RainbowSegment::run(Sign &sign, EffectData &data, uint8_t layer){
  if( sign.textChanged ){ this -> signWasUpdated(sign);}
  uint8_t segment_count = sign.segmentCount();
  CHSV curr_color = color[layer];

  if(changeOnBeat && sign.onBeat){
    color[layer].hue += beatStep[layer];
  }

  for(uint8_t i=0; i<segment_count; i++){
    Segment* curr_segment = sign.segments[i];
    curr_segment -> setColor(layer, curr_color);
    curr_color.hue += hueStep[layer];
  }

}

bool RainbowSegment::pushChar(char character, uint8_t ci){
  if( this -> useCharForColor(character, ci)){ return true; };

  int32_t val = 0xFFFF;
  String desc;

  switch(character){
    case 'w': val = (color[ci].hue += hueStep[ci]);
              desc = "Jump forward"; break;
    case 'e': val = (color[ci].hue -= hueStep[ci]);
              desc = "Jump backward"; break;

    case 's': val = (hueStep[ci] -= HUE_STEP);
              desc = STEP_SIZE_STR; break;
    case 'f': val = (hueStep[ci] += HUE_STEP);
              desc = STEP_SIZE_STR; break;
    case 'S': val = (beatStep[ci] -= HUE_STEP);
              desc = STEP_SIZE_STR; break;
    case 'F': val = (beatStep[ci] += HUE_STEP);
              desc = STEP_SIZE_STR; break;
    case 'd': val = (isStatic = !isStatic);
              desc = "Static"; break;
    case 'D': val = (changeOnBeat = !changeOnBeat);
              desc = ON_BEAT_STR; break;
    case 'x': this -> randomize(ci);
              val = hueStep[ci];
              desc = RANDOM_STR; break;
    case 'r': this -> reset();
              val = 1; desc = RESET_STR; break;
  }
  return( usedSetting(desc, val));
}

void RainbowSegment::signWasUpdated(Sign &sign){
  if(isStatic){return;}

  for(uint8_t i=0; i< LAYER_COUNT; i++){
    color[i].hue += hueStep[i];
  }
}
