/* ------------ STJORN controller --------------
 *  Code written for Teensy 3.2 micro-controller
 *  Teensy USB Type should be set to 'MIDI' 
 * 
 * https://github.com/markbrai/stjorn 
 * https://hackaday.io/project/162616-stjrn
 * 
 * https://www.gigperformer.com
 * 
 */

/* ------------ PRESETUP --------------
 * Instantiates devices used in STJORN
   ------------------------------------ */

#ifndef STJORN_DEVICES_H
#define STJORN_DEVICES_H

// *** REQUIRED LIBRARIES ***

#include <Arduino.h>
#include "STJORN_definitions.h"
#include <SPI.h>                                    // required for PlatformIO build...
#include "SparkFun_Qwiic_Twist_Arduino_Library.h"   // for rotary encoder
#include <Adafruit_GFX.h>                           // for quad alphanumeric
#include "Adafruit_LEDBackpack.h"                   // for quad alphanumeric
#include <WS2812Serial.h>                           // for neoPixels
#include <Wire.h>                                   // for i2c comms
#include <Bounce2.h>                                // for button debounce
#include "Adafruit_VCNL4010.h"                      // for proximity sensor

// Instantiate encoder
TWIST twist;

// Instantiate displays
Adafruit_AlphaNum4 display1 = Adafruit_AlphaNum4();     // left display
Adafruit_AlphaNum4 display2 = Adafruit_AlphaNum4();     // centre display
Adafruit_AlphaNum4 display3 = Adafruit_AlphaNum4();     // right display

// Instantiate WS2812Serial for LEDs
byte drawingMemory[NUM_LEDS*3];
DMAMEM byte displayMemory[NUM_LEDS*12];

WS2812Serial leds(NUM_LEDS, displayMemory, drawingMemory, PIN_WS2812, WS2812_RGB);

// Instantiate button debouncers
const uint8_t BUTTON_PINS[NUM_BUTTONS] = {23,22,21,20,17,16,15,14,33,32,31,30,28,27,26};
Bounce *buttons = new Bounce[NUM_BUTTONS];

// Instantiate proximity sensor
Adafruit_VCNL4010 vcnl;


#endif