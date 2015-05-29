#include <FastLED.h>
#include <Segment16.h>

Segment16 display;
uint32_t incomingByte = 0, input = 0;   // for incoming serial data

void setup(){
  Serial.begin(9600);
  while (!Serial) {}  // wait for Leonard
  Serial.println("Type any character to start");
  while (Serial.read() <= 0) {}
  delay(200);  // Catch Due reset problem
  display.init();
  // assume the user typed a valid character and no reset happened 
}

void loop(){
  if(Serial.available() > 0){
    input = 0;
    while(Serial.available() > 0){
      incomingByte = Serial.read();
      input = (input << 8) | incomingByte;
    }
    display.pushChar(input);
    Serial.println(input, HEX);
    //incomingByte = Serial.read();
  }
  display.show();
  delay(5);
}
