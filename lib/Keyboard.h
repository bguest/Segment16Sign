#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "Arduino.h"

class Keyboard {

  public:
    Keyboard();
    void init();
    void run();
    uint32_t data;
    bool isAvailable;
};

#endif
