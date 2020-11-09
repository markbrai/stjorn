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

#define MIC_PRESS 250      // time after which relay is triggered
#define DBL_PRESS 2000      // time within which 2 presses can be made
#define OPEN 0
#define MOMENTARY 1
#define LATCHED 2
#define WAIT 3

void processRelay(Bounce fs){

    static int relayState = OPEN;

    if(fs.fell() ){
        if(stjorn.isPressed(FS_RELAY) && relayState == WAIT && fs.previousDuration() < DBL_PRESS){ // double press latches
            usbMIDI.sendNoteOn(1,127,MIDI_CH_OS);
            triggerRelay(true);
            relayState = LATCHED;
        } else {
            if (relayState == LATCHED){     // single press to release latch
                triggerRelay(false);
                stjorn.setPressed(FS_RELAY,NOT_PRESSED);
            } else if (relayState == OPEN){             // first press
                stjorn.setPressed(FS_RELAY,PRESSED);
            }
        }
    } else if (fs.rose()){
        if (relayState == MOMENTARY){                   // release relay after continuous press
            stjorn.setPressed(FS_RELAY,NOT_PRESSED);
            triggerRelay(false);
            relayState = OPEN;
        } else if (relayState == OPEN){                 // wait for 2nd press to latch
            relayState = WAIT;
        } else if (relayState == LATCHED && !stjorn.isPressed(FS_RELAY)){   //release after cancelling latch
            relayState = OPEN;
        }

    }

    if (stjorn.isPressed(FS_RELAY) && relayState == OPEN){              // latch relay on continuous press
        if (fs.duration() >= MIC_PRESS){
            triggerRelay(true);
            relayState = MOMENTARY;
        }
    } else if (relayState == WAIT && fs.duration() > DBL_PRESS){        // timeout after single short press
        stjorn.setPressed(FS_RELAY, NOT_PRESSED);
        relayState = OPEN;
    }

}

void triggerRelay(bool state){
    
    if (state){
        digitalWrite(PIN_RELAY,HIGH);
    } else {
        digitalWrite(PIN_RELAY,LOW);
    }

}