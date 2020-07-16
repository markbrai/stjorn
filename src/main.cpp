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
#include "definitions.h"    // holds all STJORN definitions
#include "devices.h"        // holds instances of all STJORN devices

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
      leds.setPixel(i,BLUE);
  }
  leds.show();

// SETUP RELAY
  pinMode(PIN_RELAY, OUTPUT);
    
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
   * Run function for current state
   * - Process MIDI &/or footswitch messages
   * - Determine next action &/or state
   * - Determine any MIDI to be sent out
   * - Determine any update to LEDs
   * - Determine any update to screens
   * Send out MIDI as required
   * Update LEDs as required
   * Update screens as required
   * Update current state
   */

}