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
#define NUM_LEDS 14  // number of WS2812 LEDs on controller
#define PIN_WS2812 1 // WS2812 serial data sent from pin 1

// define footswitches
#define NUM_FS 15
#define NOCHANGE 0
#define FELL 1
#define ROSE 2

#define FS_ACT_MN 0 // start of 'Action' switch range
#define FS_ACT_MX 7 // end of 'Action' switch range
#define FS_ST_MN 8  // start of 'State' switch range
#define FS_ST_MX 11 // end of 'State' switch range
#define FS_ST_SONG 8
#define FS_ST_RIG 9
#define FS_ST_LOOP 10
#define FS_ST_NEXT 11
#define FS_RELAY 12 // index of 'Relay' switch
#define FS_OS_MN 13 // start of 'OnSong' switch range
#define FS_OS_MX 14 // end of 'OnSong' switch range

#define PRESSED 1
#define NOT_PRESSED 0
#define LONGPRESS 500 // longpress is > 500ms pressed state
#define PRESS_SHORT 1
#define PRESS_LONG 2

// define relay pin
#define PIN_RELAY 25

#define MIC_PRESS 250  // time after which relay is triggered
#define DBL_PRESS 1000 // time within which 2 presses can be made
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
#define EXPR_LOOP_CC 12
#define EXPR_TRAX_CC 11
#define EXPR_PADS_CC 13
#define EXPR_WAH_CC 2

// define some stuff for LEDs

#define RED 0xFF0000
#define BLUE 0x0000FF
#define GREEN 0x00FF00
#define YELLOW 0xFFFF00
#define ORANGE 0xFF7700
#define WHITE 0xFFFFFF
#define PINK 0xD4005C
#define PURPLE 0x8029CC
#define CYAN 0x42DAF5
#define DARK 0x000000
#define LED_VDIM 16
#define LED_DIM 32
#define LED_BRT 64

#define LED_SONG 6
#define LED_RIG 5
#define LED_LOOP 4
#define LED_NEXT 7
#define LED_TRANSPORT 13
#define LED_MIC 12

#define ACTION 0 // types for setLed
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
#define NUM_FX 9 // updated to 9 for auxFX // actually only 7, but includes tap tempo button
#define NUM_PATCH 8
#define NUM_ACTION 8 // number of 'action buttons'

#define FX_MOD 0
#define FX_DLY 1
#define FX_VRB 2
#define FX_TAP 3
#define FX_FLT 4
#define FX_CMP 5
#define FX_DR2 6
#define FX_DR1 7

#define CC_AUXFX 3

#define TYPE_FX_MOD 1
#define TYPE_FX_DLY 2
#define TYPE_FX_VRB 3

// define STJORN states
#define NUM_STATES 7

enum StjornState
{
  ST_TRACKS, // 0
  ST_SONG,   // 1
  ST_PATCH,  // 2
  ST_FX,     // 3
  ST_LOOP,   // 4
  ST_PADS,   // 5
  ST_WETFX,  // 6
};

// define some general parameters

#define MAX_SONGS 16 // maximum number of songs that can be switched between

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
};*/
// DEPRECATED - USED IN PREVIOUS MIDI processing

#define MIDI_CH_LIVE 16
#define MIDI_CH_GP 15
#define MIDI_CH_OS 14

/*enum ParamTgt {     // Target of incoming MIDI parameter
  TGT_NONE,         // 0. Init value, or incompatible parameter
  TGT_SONG,         // 1. Target is Song mode
  TGT_RIG,          // 2. Target is Rig Patch mode
  TGT_LOOP,         // 3. Target is Looper mode
  TGT_PADS,         // 4. Target is Pads mode
};*/
// DEPRECATED - USED IN PREVIOUS MIDI processing

#define LIVE_TAP 10

// Note for Quick Actions
#define NOTE_QA 26

// Transport MIDI from Live

#define CC_TRANSPORT 1
#define CC_VAL_PLAY 127
#define CC_VAL_STOP 0
#define CC_VAL_CLICK 64
#define CC_VAL_SONG 32

#define CC_STOP 2
#define CC_VAL_STOP_OUT 127
#define CC_VAL_SOFTSTOP 64

#define CC_TRAXMUTE 29
#define CC_VAL_TRAX_MUTE 127
#define CC_VAL_TRAX_UNMUTE 0

#define CC_CUEMUTE 28
#define CC_VAL_CUE_MUTE 127
#define CC_VAL_CUE_UNMUTE 0

#define CC_CYCLE 5
#define CC_VAL_NEXT 0
#define CC_VAL_ONESHOT 64
#define CC_VAL_CYCLE 127

#define CC_CYCLETOG 4
#define CC_VAL_CYCTOG 127

#define CC_CYCLEOK 27
#define CC_VAL_CYCLE_OK 127
#define CC_VAL_CYCLE_NOK 0

#define CC_GOTO1 6
#define CC_GOTO2 7
#define CC_GOTO3 8
#define CC_GOTO4 9
#define CC_VAL_GOTO 127

// Transport Values
#define TRAN_STOP 0
#define TRAN_PLAY 1
#define TRAN_CYCLE 2
#define TRAN_GOTO 3

#define FLW_NEXT 0
#define FLW_ONESHOT 1
#define FLW_CYCLE 2
#define FLW_GOTO1 3
#define FLW_GOTO2 4
#define FLW_GOTO3 5
#define FLW_GOTO4 6

// Some stuff for the Looper
#define CC_LOOPER_IN 50
#define LOOPER_STOP 0
#define LOOPER_RECORD 1
#define LOOPER_PLAY 2
#define LOOPER_OVERDUB 3

// Sysex Stuff
#define SYS_BYTE_ID 1
#define SYS_BYTE_TYPE 2
#define SYS_BYTE_CURR 3
#define SYS_BYTE_G1 7
#define SYS_BYTE_G2 11
#define SYS_BYTE_G3 15
#define SYS_BYTE_G4 19
#define SYS_BYTE_NEXT 23
#define SYSEX_STJORN 102
#define SYSEX_SCENES 83

#define SCENE_CURR 0
#define SCENE_G1 1
#define SCENE_G2 2
#define SCENE_G3 3
#define SCENE_G4 4
#define SCENE_NEXT 5

#endif
