#include "Helpers.h"

bool usedSetting(String desc, int32_t val){
  if(val != 0xFFFF){
    Serial.print(desc);
    Serial.print(": ");
    Serial.print(val);
    Serial.println(" ");

    Serial1.print('\n');
    Serial1.print(desc);
    Serial1.print(": ");
    Serial1.print(val);
    return true;
  }
  return false;
}

