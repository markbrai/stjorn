
#include <Arduino.h>
#include "STJORN_definitions.h"    // holds all STJORN definitions
#include <WS2812Serial.h>                           // for neoPixels

void controlAnLed(WS2812Serial *leds){

    leds->setPixel(1,GREEN);
    leds->show();

}