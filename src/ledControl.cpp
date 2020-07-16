#include <WS2812Serial.h>                           // for neoPixels
#include <Arduino.h>
#include "STJORN_definitions.h"    // holds all STJORN definitions

void controlAnLed(){

    leds.setPixel(1,GREEN);
    leds.show();

}