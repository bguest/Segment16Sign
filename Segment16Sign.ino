#include <FastLED.h>
#include <Segment16.h>

Segment16 display;

void setup(){
   Serial.begin(9600);
}

void loop(){
  display.show();
  delay(2);
}
