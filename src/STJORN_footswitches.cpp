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

/* ------------ FOOTSWITCHES --------------
 *  Functions for processing footswitches
 *  ---------------------------------------- */

#include "STJORN_definitions.h"
#include "STJORN_stateClass.h"
#include "SparkFun_Qwiic_Twist_Arduino_Library.h"
#include <Bounce2.h>

extern TWIST twist;

void updateFootswitches(Bounce *fs) {

  for (int i = 0; i < NUM_FS; i++) {
    fs[i].update();
  }
}

int fsShortLong(Bounce fs, int fsNum) {

  if (fs.fell()) {
    stjorn.setPressed(fsNum, PRESSED);
  } else if (fs.rose() && stjorn.isPressed(fsNum)) {
    stjorn.setPressed(fsNum, NOT_PRESSED);
    Serial.print("PRESS_SHORT");
    return PRESS_SHORT;
  }

  if (stjorn.isPressed(fsNum)) {
    if (fs.duration() >= LONGPRESS) {
      stjorn.setPressed(fsNum, NOT_PRESSED);
      Serial.print("PRESS_LONG");
      return PRESS_LONG;
    }
  }

  return 0;
}

bool fsTapEngage(Bounce fs, int fsNum) {

#define ENGAGED 1
#define LOCKED 0
#define TAP_TIMEOUT 10000

  // static bool tapEngage = LOCKED;

  // if (stjorn.stateChange()){      // reset tapEngage status when state
  // changes
  //     //tapEngage = LOCKED;
  //     stjorn.setTap(LOCKED);
  // }

  // if (fs.fell() ){
  //     stjorn.setPressed(fsNum,PRESSED);
  //     if (stjorn.tap() == ENGAGED){
  //         return true;
  //     }
  // } else if (fs.rose() && stjorn.isPressed(fsNum) ){
  //     stjorn.setPressed(fsNum,NOT_PRESSED);
  //     if (stjorn.tap() == ENGAGED){
  //         return true;
  //     }
  // }

  // if (stjorn.isPressed(fsNum) ){
  //     if (fs.duration() >= LONGPRESS){
  //         stjorn.setPressed(fsNum,NOT_PRESSED);
  //         //tapEngage = ENGAGED;
  //         stjorn.setTap(ENGAGED);
  //     }
  // }

  // if (!stjorn.isPressed(fsNum) && stjorn.tap() == ENGAGED){
  //     if (fs.duration() >= TAP_TIMEOUT){
  //         stjorn.setTap(LOCKED);
  //     }
  // }

  stjorn.setTap(ENGAGED);

  // return false;
  return true;
}

void updateExpression(int prox) {
  // conversion from raw proximity to MIDI value
  int proxMidi = 0;

  if (prox <= PROX_MIN) {
    proxMidi = 127;
  } else if (prox >= PROX_MAX) {
    proxMidi = 0;
  } else {
    proxMidi = map(prox, PROX_MAX, PROX_MIN, 0, 127); // scale proximity to MIDI
  }
  stjorn.setProx(proxMidi);
}

void sendExpression() {

  /*if (stjorn.exprChanged() ){         // expression MIDI value is updated
      usbMIDI.sendControlChange(cc, stjorn.expression(), channel);
  }*/

  if (stjorn.exprChanged()) {
    int exprType = stjorn.exprType();
    int channel;

    if (exprType == EXPR_GTR_CC || exprType == EXPR_WAH_CC) {
      channel = MIDI_CH_GP;
    } else {
      channel = MIDI_CH_LIVE;
    }

    usbMIDI.sendControlChange(exprType, stjorn.expression(), channel);
  }
}
}

void updateTwist() {
  // Read the twist
  twist.update(); // Update the twist state (required significantly for encoder
                  // count)

  // Check for click
  if (twist.isClicked()) {
    if (stjorn.state() == ST_MENU) {
      // If in menu, maybe select? Or exit?
      // For now, let's treat click as EXIT from menu for simplicity in testing
      stjorn.setState(ST_PATCH); // Go back to default patch state
    } else {
      // If not in menu, enter menu
      stjorn.setState(ST_MENU);
    }
  }

  // Check for rotation if in MENU
  if (stjorn.state() == ST_MENU) {
    int diff = twist.getDiff();
    if (diff != 0) {
      int currentItem = stjorn.menuItem();
      currentItem += diff;
      // Simple bound checking 0-10 for now
      if (currentItem < 0)
        currentItem = 0;
      if (currentItem > 10)
        currentItem = 10;
      stjorn.setMenuItem(currentItem);
    }
  }
}