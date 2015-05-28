#include <FastLED.h>
#include <Segment16.h>

Segment16 display;

void setup(){
  Serial.begin(9600);
  while (!Serial) {}  // wait for Leonardo
  Serial.println("Type any character to start");
  while (Serial.read() <= 0) {}
  delay(200);  // Catch Due reset problem
  // assume the user typed a valid character and no reset happened 
}

void loop(){
  Serial.println("LOOP");
  display.show();
  delay(1000);
}
