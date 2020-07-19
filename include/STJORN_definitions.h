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

// define some general parameters

#define MAX_SONGS 14    // maximum number of songs that can be switched between

// define some MIDI parameters

enum MidiType {  // Types of MIDI message to be received
  MIDI_NONE,     // 0. Init value, or no new MIDI message
  MIDI_PROG,     // 1. Program Change
  MIDI_NOTEON,   // 2. Note On
  MIDI_NOTEOFF,  // 3. Note Off
  MIDI_CC,       // 4. Control Change
  MIDI_START,
  MIDI_STOP,
  MIDI_CONTINUE,
  MIDI_CLOCK,
};

#define MIDI_CH_LIVE 16
#define MIDI_CH_GP 15
#define MIDI_CH_OS 14

enum ParamTgt {     // Target of incoming MIDI parameter
  TGT_NONE,         // 0. Init value, or incompatible parameter
  TGT_SONG,         // 1. Target is Song mode
  TGT_RIG,          // 2. Target is Rig Patch mode
  TGT_LOOP,         // 3. Target is Looper mode
  TGT_PADS,         // 4. Target is Pads mode
};

enum LiveParam {
  LIVE_NONE,        // 0. Init value, or incompatible parameter
  LIVE_TRANSPORT,   // 1. Play, Click-only, Stop
  LIVE_STOPTYPE,    // 2. Type of Stop (soft, hard, or none [playing])
  LIVE_PANIC,       // 3. PANIC!!!!
  LIVE_CYCLETOG,    // 4. Toggle of cycle modes
  LIVE_CYCLE,       // 5. Cycle type (One-shot, loop, none)
  LIVE_GOTO1,       // 6. Goto 1
  LIVE_GOTO2,       // 7. Goto 2
  LIVE_GOTO3,       // 8. Goto 3
  LIVE_GOTO4,       // 9. Goto 4
  LIVE_TAP,         // 10. Tap tempo
  LIVE_TRAXVOL,     // 11. Trax volume
  LIVE_LOOPVOL,     // 12. Looper volume
  LIVE_PADVOL,      // 13. Pads volume
  LIVE_VERSE,       // 14. Verse song section
  LIVE_CHORUS,      // 15. Chorus song section
  LIVE_BRIDGE,      // 16. Bridge song section
  LIVE_PRECH,       // 17. Pre-chorus song section
  LIVE_TAG,         // 18. Tag song section
  LIVE_TURN,        // 19. Turn song section
  LIVE_INTRO,       // 20. Intro song section
  LIVE_OUTRO,       // 21. Outro song section
  LIVE_CLICK,       // 22. Click only song section
  LIVE_COUNT,       // 23. Count song section
  LIVE_END,         // 24. End song section
  LIVE_CONTR,       // 25. Contribution song section
  LIVE_SPACE,       // 26. Spacer song section
  LIVE_CYCLEOK,     // 27. Cycle OK or Not
};




#endif