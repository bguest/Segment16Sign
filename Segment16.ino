#include <FastLED.h>
#include <Segment16.h>

Segment16 display;

void setup(){
  display.init();
}

void loop(){
  display.run();
}
