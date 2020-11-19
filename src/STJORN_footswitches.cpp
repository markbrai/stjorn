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

#include <Bounce2.h>
#include "STJORN_definitions.h"
#include "STJORN_stateClass.h"

void updateFootswitches(Bounce *fs){

    for (int i=0; i < NUM_FS; i++){
        fs[i].update();
    }
}

int fsShortLong(Bounce fs, int fsNum){

    if (fs.fell() ){
        stjorn.setPressed(fsNum,PRESSED);
    } else if (fs.rose() && stjorn.isPressed(fsNum) ){
        stjorn.setPressed(fsNum, NOT_PRESSED);
        return PRESS_SHORT;
    }

    if (stjorn.isPressed(fsNum) ){
        if (fs.duration() >= LONGPRESS){
            stjorn.setPressed(fsNum,NOT_PRESSED);
            return PRESS_LONG;
        }
    }

    return 0;

}

bool fsTapEngage(Bounce fs, int fsNum){

    #define ENGAGED 1
    #define LOCKED 0
    #define TAP_TIMEOUT 10000

    static bool tapEngage = LOCKED;

    if (stjorn.stateChange()){      // reset tapEngage status when state changes
        tapEngage = LOCKED; 
    }
    
    if (fs.fell() ){
        stjorn.setPressed(fsNum,PRESSED);
        if (tapEngage == ENGAGED){
            return true;
        }
    } else if (fs.rose() && stjorn.isPressed(fsNum) ){
        stjorn.setPressed(fsNum,NOT_PRESSED);
    }

    if (stjorn.isPressed(fsNum) ){
        if (fs.duration() >= LONGPRESS){
            stjorn.setPressed(fsNum,NOT_PRESSED);
            tapEngage = ENGAGED;
        }
    }

    if (!stjorn.isPressed(fsNum) && tapEngage == ENGAGED){
        if (fs.duration() >= TAP_TIMEOUT){
            tapEngage = LOCKED;
        }
    }

    return false;
}

void updateExpression(int prox){
// conversion from raw proximity to MIDI value
int proxMidi = 0;

    if (prox <= PROX_MIN) {
        proxMidi = 127;
    } else if (prox >= PROX_MAX) {
        proxMidi = 0; 
    } else {
        proxMidi = map(prox,PROX_MAX,PROX_MIN,0,127);    // scale proximity to MIDI
    }
    stjorn.setProx(proxMidi);

}

void sendExpression(int cc, int channel){

    if (stjorn.exprChanged() ){         // expression MIDI value is updated
        usbMIDI.sendControlChange(cc, stjorn.expression(), channel);
    }

}