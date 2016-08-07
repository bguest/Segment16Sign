#include "Seizure.h"

Seizure::Seizure(){
  for(uint8_t i=0; i<LAYER_COUNT; i++){
    lastChange[i] = 0;
    colorIdx[i] = 0;
  }
  this -> reset();
}

void Seizure::reset(){
  for(uint8_t j=0; j<LAYER_COUNT; j++){
    flashPerBeat[j] = 4;
    for(uint8_t i=0; i<SEIZURE_COLOR_COUNT; i++){
      colors[i][j] = CHSV(random(255), 0, 255*(i%2));
    }
  }
}

void Seizure::randomize(uint8_t ci){
  flashPerBeat[ci] = random(1,10);
  for(uint8_t i=0; i<SEIZURE_COLOR_COUNT; i++){
    colors[i][ci] = CHSV(random(255), random(255), random(255));
  }
}

void Seizure::run(Sign &sign, EffectData &data, uint8_t ci){
  unsigned long time = millis();
  if(time - lastChange[ci] < data.tempo/flashPerBeat[ci]){ return; }
  lastChange[ci] = time;

  uint8_t segment_count = sign.segmentCount();
  colorIdx[ci] = (colorIdx[ci]+1) % SEIZURE_COLOR_COUNT;
  CHSV clr = colors[colorIdx[ci]][ci];

  for(uint8_t i=0; i<segment_count; i++){
    Segment* curr_segment = sign.segments[i];
    curr_segment -> setColor(ci, clr);
  }

}
bool Seizure::pushChar(char character, uint8_t ci){
  if( this -> useCharForColor(character, ci)){
    colors[editIdx][ci] = color[ci];
    return true;
  }

  int32_t val = 0xFFFF;
  String desc;

  switch(character){
    case 's': val = flashPerBeat[ci] = max(0, flashPerBeat[ci]-1);
              desc = STEP_SIZE_STR; break;
    case 'f': val = ++flashPerBeat[ci];
              desc = STEP_SIZE_STR; break;

    case 'S': val = editIdx = (editIdx-1) % SEIZURE_COLOR_COUNT;
              desc = INDEX_STR; break;
    case 'F': val = editIdx = (editIdx+1) % SEIZURE_COLOR_COUNT;
              desc = INDEX_STR; break;
    case 'x': this -> randomize(ci);
              desc = RANDOM_STR; break;
              break;
    case 'z': this -> reset();
              val = 1; desc = RESET_STR; break;
  }

  return( usedSetting(desc, val));
}


