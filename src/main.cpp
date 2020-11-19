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
#include "STJORN_definitions.h"                     // holds all STJORN definitions
#include <SPI.h>                                    // required for PlatformIO build...
#include "SparkFun_Qwiic_Twist_Arduino_Library.h"   // for rotary encoder
#include <Adafruit_GFX.h>                           // for quad alphanumeric
#include "Adafruit_LEDBackpack.h"                   // for quad alphanumeric
#include <WS2812Serial.h>                           // for neoPixels
#include <Wire.h>                                   // for i2c comms
#include <Bounce2.h>                                // for button debounce
#include "Adafruit_VCNL4010.h"                      // for proximity sensor
#include "STJORN_footswitches.h"                    // STJORN Footswitch functions
#include "STJORN_stateClass.h"                      // STJORN main state variables
#include "STJORN_statePatch.h"                      // STJORN state functions for PATCH
#include "STJORN_stateFX.h"
#include "STJORN_midi.h"

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
/* Button orders:
*  
*/
const uint8_t FS_PINS[NUM_FS] = {33,32,31,30,20,21,22,23,15,16,17,14,27,28,26};
Bounce *fs = new Bounce[NUM_FS];

// Instantiate proximity sensor
Adafruit_VCNL4010 vcnl;

Stjorn stjorn;


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

  char splash[6] = {'S','T','J','O','R','N'};

  display1.writeDigitAscii(3,splash[0]);
  display2.writeDigitAscii(0,splash[1]);
  display2.writeDigitAscii(1,splash[2]);
  display2.writeDigitAscii(2,splash[3]);
  display2.writeDigitAscii(3,splash[4]);
  display3.writeDigitAscii(0,splash[5]);

// write displays
  display1.writeDisplay();
  display2.writeDisplay();
  display3.writeDisplay();

// TWIST SETUP
  twist.begin();

// LED SETUP
  leds.begin();
  leds.setBrightness(LED_VDIM);
  for(int i = 0; i < NUM_LEDS; i++) {
      leds.setPixel(i,RED);
  }
  leds.show();

// SETUP RELAY
  pinMode(PIN_RELAY, OUTPUT);


// SETUP FOOTSWITCHES
  for (int i = 0; i < NUM_FS; i++) {
    fs[i].attach( FS_PINS[i] , INPUT_PULLUP  );       //setup the bounce instance for the current button
    fs[i].interval(5);                               // interval in ms
  }


delay(2000);    // keep STJORN 'splash' on screen for a few seconds

  for(int i = 0; i < NUM_LEDS; i++) {
      leds.setPixel(i,DARK);              // turn all LEDs 'off'
  }
  leds.show();

  //Serial.begin(9600);

  // clear screen buffers
  int digits[4] = {DIGIT_SONG,DIGIT_CURR,DIGIT_NEXT,DIGIT_RIG};

  for (int blk = 0; blk < 4; blk++){
    int numDigits = digits[blk];
    for (int i = 0; i < numDigits; i++){
      stjorn.setDisplay(blk,i,' ');
    }
  }

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
   * Read encoder
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
   * Update Menu
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
   */

// UPDATE AND PROCESS MIDI

  if (usbMIDI.read() ){

    processMidi();

  }


// UPDATE FOOTSWITCHES

  updateFootswitches(fs);

// UPDATE EXPRESSION PEDALS


// SELECT AND PROCESS STATES
/* Each state is responsible for handling footswitch and expression actions
 * plus setting correct displays and leds based on received MIDI or state
 * changes
 */

  switch (stjorn.state()){
    case ST_TRACKS:

      break;
    
    case ST_SONG:

      break;

    case ST_PATCH:
      statePatch(fs);
      break;

    case ST_FX:
      stateFX(fs);
      break;

    case ST_LOOP:

      break;

    case ST_PADS:

      break;

    default:
      break;
  }


// Set LEDs 
  for (int i = 0; i < NUM_LEDS; i++){
    int colour;
    if (stjorn.isLit(i) ){
      colour = stjorn.isColour(i);
    } else {
      colour = DARK;
    }
    leds.setPixel(i,colour);
  }
  leds.show();

// Set Displays

  display1.writeDigitAscii(0,stjorn.ascii(BLK_SONG,0));
  display1.writeDigitAscii(1,stjorn.ascii(BLK_SONG,1));
  display1.writeDigitAscii(2,stjorn.ascii(BLK_CURR,0));
  display1.writeDigitAscii(3,stjorn.ascii(BLK_CURR,1));
  display1.writeDisplay();

  display2.writeDigitAscii(0,stjorn.ascii(BLK_CURR,2));
  display2.writeDigitAscii(1,stjorn.ascii(BLK_CURR,3));
  display2.writeDigitAscii(2,stjorn.ascii(BLK_NEXT,0));
  display2.writeDigitAscii(3,stjorn.ascii(BLK_NEXT,1));
  display2.writeDisplay();

  display3.writeDigitAscii(0,stjorn.ascii(BLK_NEXT,2));
  display3.writeDigitAscii(1,stjorn.ascii(BLK_NEXT,3));
  display3.writeDigitAscii(2,stjorn.ascii(BLK_RIG,0));
  display3.writeDigitAscii(3,stjorn.ascii(BLK_RIG,1));
  display3.writeDisplay();

  
}