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
#define NUM_FS 15
#define NOCHANGE 0
#define FELL 1
#define ROSE 2

#define FS_ACT_MN 0    // start of 'Action' switch range
#define FS_ACT_MX 7    // end of 'Action' switch range 
#define FS_ST_MN 8     // start of 'State' switch range
#define FS_ST_MX 11     // end of 'State' switch range
#define FS_ST_SONG 8
#define FS_ST_RIG 9
#define FS_ST_LOOP 10
#define FS_ST_NEXT 11
#define FS_RELAY 12     // index of 'Relay' switch
#define FS_OS_MN 13     // start of 'OnSong' switch range
#define FS_OS_MX 14     // end of 'OnSong' switch range

#define PRESSED 1
#define NOT_PRESSED 0

#define LONGPRESS 500     // longpress is > 500ms pressed state
#define PRESS_SHORT 1
#define PRESS_LONG 2

// define relay pin
#define PIN_RELAY 25

#define MIC_PRESS 250      // time after which relay is triggered
#define DBL_PRESS 1000      // time within which 2 presses can be made
#define OPEN 0
#define MOMENTARY 1
#define LATCHED 2
#define WAIT 3

// define power LED pin
#define PIN_PWRLED 13

// define expression pedal stuff
#define PIN_EXP 29
#define PROX_MIN 6500
#define PROX_MAX 30000
#define EXPR_GTR_CC 1

// define some stuff for LEDs

#define RED 0xFF0000
#define BLUE 0x0000FF
#define GREEN 0x00FF00
#define YELLOW 0xFFFF00
#define ORANGE 0xFF7700
#define WHITE 0xFFFFFF
#define PINK 0xD4005C
#define PURPLE 0x8029CC
#define DARK 0x000000
#define LED_VDIM 16
#define LED_DIM 32
#define LED_BRT 64

#define LED_SONG 6
#define LED_RIG 5
#define LED_LOOP 4
#define LED_NEXT 7
#define LED_TRANSPORT 12
#define LED_MIC 13

#define ACTION 0      // types for setLed
#define STATE 1
#define NEXT 2
#define MIC 3
#define TRANSPORT 4

// define some stuff for screens

#define SCRN_DIM 4
#define SCRN_BRT 6

#define BLK_SONG 0
#define BLK_CURR 1
#define BLK_NEXT 2
#define BLK_RIG 3

#define DIGIT_SONG 2
#define DIGIT_CURR 4
#define DIGIT_NEXT 4
#define DIGIT_RIG 2

// define some things for FX and Patches
#define NUM_FX 8    // actually only 7, but include tap tempo button
#define NUM_PATCH 8
#define NUM_ACTION 8 // number of 'action buttons' 

// define STJORN states
#define NUM_STATES 6

enum StjornState {    
  ST_TRACKS,    // 0
  ST_SONG,      // 1
  ST_PATCH,     // 2
  ST_FX,        // 3
  ST_LOOP,      // 4
  ST_PADS,      // 5
};

// define some general parameters

#define MAX_SONGS 16    // maximum number of songs that can be switched between

// define some MIDI parameters

/*enum MidiType {  // Types of MIDI message to be received
  MIDI_NONE,     // 0. Init value, or no new MIDI message
  MIDI_PROG,     // 1. Program Change
  MIDI_NOTEON,   // 2. Note On
  MIDI_NOTEOFF,  // 3. Note Off
  MIDI_CC,       // 4. Control Change
  MIDI_START,
  MIDI_STOP,
  MIDI_CONTINUE,
  MIDI_CLOCK,
};*/    // DEPRECATED - USED IN PREVIOUS MIDI processing

#define MIDI_CH_LIVE 16
#define MIDI_CH_GP 15
#define MIDI_CH_OS 14

/*enum ParamTgt {     // Target of incoming MIDI parameter
  TGT_NONE,         // 0. Init value, or incompatible parameter
  TGT_SONG,         // 1. Target is Song mode
  TGT_RIG,          // 2. Target is Rig Patch mode
  TGT_LOOP,         // 3. Target is Looper mode
  TGT_PADS,         // 4. Target is Pads mode
};*/ // DEPRECATED - USED IN PREVIOUS MIDI processing

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