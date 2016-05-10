#include "Pixel.h"
#include "Color16.h"

Pixel::Pixel(){
  hsv16 = CHSV16(0,0,0);
};

void Pixel::setColor(CHSV clr){
  hsv16.hue = clr.hue << 8;
  hsv16.sat = clr.sat << 8;
  hsv16.val = clr.val << 8;
}

void Pixel::setHue16(uint16_t hue){
  hsv16.hue = hue;
}

void Pixel::addHue16(int16_t deltaHue){
  hsv16.hue += deltaHue;
}

uint16_t Pixel::getHue16(){
  return hsv16.hue;
}

CHSV Pixel::getColor(){
  CHSV color;
  color.hue = (hsv16.hue >> 8);
  color.sat = (hsv16.sat >> 8);
  color.val = (hsv16.val >> 8);
  return color;
}

CHSV16 Pixel::getHsv16(){
  return hsv16;
}

void Pixel::setHsv16(CHSV16 clr){
  hsv16 = clr;
}

