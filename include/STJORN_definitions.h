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
 * Definitions, enums, etc used in STJORN
   ------------------------------------ */

#ifndef STJORN_DEFINITIONS_H
#define STJORN_DEFINITIONS_H

// define LEDs 
#define NUM_LEDS 14       // number of WS2812 LEDs on controller
#define PIN_WS2812 1      // WS2812 serial data sent from pin 1

// define footswitches
#define NUM_BUTTONS 15

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

// define some MIDI parameters

enum MidiType {
  MIDI_NONE,     // 0. Init value, or no new MIDI message
  MIDI_PROG,     // 1. Program Change
  MIDI_NOTEON,   // 2. Note On
  MIDI_NOTEOFF,  // 3. Note Off
  MIDI_CC,       // 4. Control Change
};

#define MIDI_CH_LIVE 16
#define MIDI_CH_GP 15
#define MIDI_CH_OS 14



#endif