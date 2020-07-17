/* ------------ STJORN controller --------------
 *  Code written for Teensy 3.2 micro-controller
 *  Teensy USB Type should be set to 'MIDI' 
 * 
 * https://github.com/markbrai/stjorn 
 * https://hackaday.io/project/162616-stjrn
 * 
 * https://www.gigperformer.com
 * 
 * Mark Braithwaite, 2020
 * 
 */

#include <Arduino.h>
#include "STJORN_definitions.h"    // holds all STJORN definitions
//#include "STJORN_devices.h"        // holds instances of all STJORN devices
#include <SPI.h>                                    // required for PlatformIO build...
#include "SparkFun_Qwiic_Twist_Arduino_Library.h"   // for rotary encoder
#include <Adafruit_GFX.h>                           // for quad alphanumeric
#include "Adafruit_LEDBackpack.h"                   // for quad alphanumeric
#include <WS2812Serial.h>                           // for neoPixels
#include <Wire.h>                                   // for i2c comms
#include <Bounce2.h>                                // for button debounce
#include "Adafruit_VCNL4010.h"                      // for proximity sensor
#include "ledControl.h"

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


void setup() {

// TURN POWER LED ON
  pinMode(PIN_PWRLED, OUTPUT);
  digitalWrite(PIN_PWRLED, HIGH);

// DISPLAY SETUP
// NOTE: displays should be started before TWIST. For some reason...
// start displays
  display1.begin(0x70);
  display2.begin(0x71);
  display3.begin(0x72);

// set display brightness
  display1.setBrightness(SCRN_DIM);
  display2.setBrightness(SCRN_DIM);
  display3.setBrightness(SCRN_DIM);

// setup welcome message
  display1.writeDigitAscii(3,'S');
  display2.writeDigitAscii(0,'T');
  display2.writeDigitAscii(1,'J');
  display2.writeDigitAscii(2,'O');
  display2.writeDigitAscii(3,'R');
  display3.writeDigitAscii(0,'N');

// write displays
  display1.writeDisplay();
  display2.writeDisplay();
  display3.writeDisplay();

// TWIST SETUP
  twist.begin();

// LED SETUP
  leds.begin();
  leds.setBrightness(LED_DIM);
  for(int i = 0; i < NUM_LEDS; i++) {
      leds.setPixel(i,RED);
  }
  leds.show();

// SETUP RELAY
  pinMode(PIN_RELAY, OUTPUT);


delay(5000);


}


void loop() {
  // put your main code here, to run repeatedly:

  /* Functions to run (not explicitly in order)
   * Read incoming MIDI
   * Process MIDI (determine type, number, value, etc)
   * Read footswitches
   * Process inputs (aggregate MIDI and FS values and determine priority)
   * Check if relay or OnSong buttons pressed (global actions, not tied to a particular state)
   * Check current state (mode)
   * Run function for current state --> Always run current function (and react internally to no input)? Or skip if no input on this cycle?
   * - Process MIDI &/or footswitch messages
   * - Determine next action &/or state (if any)
   * - Determine any MIDI to be sent out
   * - Determine any update to LEDs
   * - Determine any update to screens
   * Send out MIDI as required
   * Update LEDs as required
   * Update screens as required
   * Update current state
   */

  for(int i = 0; i < NUM_LEDS; i++) {
      leds.setPixel(i,DARK);
  }
  leds.show();

// pass leds object in here
  controlAnLed();
  


}