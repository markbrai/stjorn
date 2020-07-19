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
#include "ledControl.h"
//#include "STJORN_devices.h"        // holds instances of all STJORN devices
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

  for(int i = 0; i < NUM_LEDS; i++) {
      leds.setPixel(i,DARK);
  }
  leds.show();

// pass leds object in here
  controlAnLed(&leds);


}


void loop() {
 
  /* Control methodology
   * Controller sends out MIDI - or sets internal mode - on footswitch press
   * LEDs and Screens are set by MIDI feedback from Live/Gp
   * - e.g. FX LEDs set on feedback from GP, transport set on feedback from Live
   * 
   */

  /* Functions to run:
   * Read incoming MIDI
   * Read footswitches
   * Read expression pedal
   * Process MIDI (determine channel, type, number, value)
   * Process footswitches (from current state, what is FS action)
   * - Also includes priority check if MIDI and FS 'clash'
   * Process expression pedal
   * - MIDI channel and CC depending on current state
   * Update transport state machine as required
   * - What LEDs to light (bypass if not in Song mode currently)
   * - What screen updates
   * Update rig state machine as required
   * - What LEDs to light (bypass if not in Rig mode currently)
   * - What screen updates
   * Update looper state machine as required
   * - What LEDs to light (bypass if not in Song mode currently)
   * - What screen updates (bypass if not in looper mode currently)
   * Update pads state machine as required
   * - What LEDs to light (bypass if not in Pads mode currently)
   * - What screen updates (bypass if not in Pads mode currently)
   * Set relay as required
   * Send out MIDI as required
   * Update LEDs as required
   * Update Screens as required
   * Update overall state (was mode changed by Footswitch)
   */



  /* What needs to be updated in the background, no matter the state:
   * Song state/transport sync with Live  --> Updated via MIDI from Live
   * - Sets screen text for song sections
   * - Sets colour of transport LED
   * Current song   --> Updated from Prog.Ch from either GP or Live
   * - Sets screen text for song num
   * - Sets MIDI prog.ch. to send out on 'next song' button press
   * Current Song Part --> updated from MIDI from GP
   * - Sets screen text for song part
   * 
   * 
   */

  
}