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


// *** REQUIRED LIBRARIES ***
#include <SPI.h>                                    // required for PlatformIO build...
#include "SparkFun_Qwiic_Twist_Arduino_Library.h"   // for rotary encoder
#include <WS2812Serial.h>                           // for neoPixels
#include <Wire.h>                                   // for i2c comms
#include <Adafruit_GFX.h>                           // for quad alphanumeric
#include "Adafruit_LEDBackpack.h"                   // for quad alphanumeric
#include <Bounce2.h>                                // for button debounce
#include "Adafruit_VCNL4010.h"                      // for proximity sensor
 

// *** DEVICE INSTANTIATION & DEFINITIONS ***

// Instantiate encoder
TWIST twist;

// Instantiate displays
Adafruit_AlphaNum4 display1 = Adafruit_AlphaNum4();     // left display
Adafruit_AlphaNum4 display2 = Adafruit_AlphaNum4();     // centre display
Adafruit_AlphaNum4 display3 = Adafruit_AlphaNum4();     // right display

// Instantiate WS2812Serial 
#define NUM_LEDS 14       // number of WS2812 LEDs on controller
#define PIN_WS2812 1      // WS2812 serial data sent from pin 1

byte drawingMemory[NUM_LEDS*3];
DMAMEM byte displayMemory[NUM_LEDS*12];

WS2812Serial leds(NUM_LEDS, displayMemory, drawingMemory, PIN_WS2812, WS2812_RGB);


// Instantiate button debouncing
#define NUM_BUTTONS 15
const uint8_t BUTTON_PINS[NUM_BUTTONS] = {23,22,21,20,17,16,15,14,33,32,31,30};
Bounce * buttons = new Bounce[NUM_BUTTONS];


// Instantiate proximity sensor
Adafruit_VCNL4010 vcnl;


// *** DEFINITION OF OTHER BITS ***

// define relay pin
#define PIN_RELAY 25

// define power LED pin
#define PIN_PWRLED 13

// define expression pedal input pin
#define PIN_EXP 29

// define some colours and brightness

#define RED 0xFF0000
#define BLUE 0x0000FF
#define GREEN 0x00FF00
#define DARK 0x000000
#define LED_DIM 32
#define LED_BRT 64

#define SCRN_DIM 4
#define SCRN_BRT 6
