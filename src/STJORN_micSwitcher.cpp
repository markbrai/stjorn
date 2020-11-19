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

/* ------------ MIC SWITCHER --------------
*  Functions for controlling mic switcher relay
*  ---------------------------------------- */

#include <Bounce2.h>
#include "STJORN_definitions.h"
#include "STJORN_stateClass.h"
#include "STJORN_micSwitcher.h"



void processRelay(Bounce fs){

    if(fs.fell() ){
        if(stjorn.isPressed(FS_RELAY) && stjorn.relay() == WAIT && fs.previousDuration() < DBL_PRESS){ // double press latches
            usbMIDI.sendNoteOn(1,127,MIDI_CH_OS);         // for debugging
            triggerRelay(true);
            stjorn.setRelay(LATCHED);
        } else {
            if (stjorn.relay() == LATCHED){     // single press to release latch
                triggerRelay(false);
                stjorn.setPressed(FS_RELAY,NOT_PRESSED);
            } else if (stjorn.relay() == OPEN){             // first press
                stjorn.setPressed(FS_RELAY,PRESSED);
            }
        }
    } else if (fs.rose()){
        if (stjorn.relay() == MOMENTARY){                   // release relay after continuous press
            stjorn.setPressed(FS_RELAY,NOT_PRESSED);
            triggerRelay(false);
            stjorn.setRelay(OPEN);
        } else if (stjorn.relay() == OPEN){                 // wait for 2nd press to latch
            stjorn.setRelay(WAIT);
        } else if (stjorn.relay() == LATCHED && !stjorn.isPressed(FS_RELAY)){   //release after cancelling latch
            stjorn.setRelay(OPEN);
        }

    }

    if (stjorn.isPressed(FS_RELAY) && stjorn.relay() == OPEN){              // latch relay on continuous press
        if (fs.duration() >= MIC_PRESS){
            triggerRelay(true);
            stjorn.setRelay(MOMENTARY);
        }
    } else if (stjorn.relay() == WAIT && fs.duration() > DBL_PRESS){        // timeout after single short press
        stjorn.setPressed(FS_RELAY, NOT_PRESSED);
        stjorn.setRelay(OPEN);
    }

}

void triggerRelay(bool state){
    
    if (state){
        digitalWrite(PIN_RELAY,HIGH);
    } else {
        digitalWrite(PIN_RELAY,LOW);
    }

}