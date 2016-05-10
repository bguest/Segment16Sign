#include "Keyboard.h"

Keyboard::Keyboard(){
  isAvailable = false;
  data = 0;
}

void Keyboard::init(){
}

void Keyboard::run(){

  uint32_t incomingByte = 0;

  if(Serial.available() > 0 || Serial1.available()){
    data = 0;
    while(Serial.available() > 0){
      incomingByte = Serial.read();
      data = (data << 8) | incomingByte;
    }
    while(Serial1.available()){
      incomingByte = Serial1.read();
      data = (data << 8) | incomingByte;
    }
    isAvailable = true;
    //Serial.println(input, HEX);
    //Serial1.println(input, HEX);
    //incomingByte = Serial.read();
  }else{
    isAvailable = false;
  }

}
