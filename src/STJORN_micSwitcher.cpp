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

void processRelay(Bounce fs){

    if(fs.fell() ){
        stjorn.setPressed(FS_RELAY,PRESSED);
    } else if (fs.rose()){
        stjorn.setPressed(FS_RELAY,NOT_PRESSED);
        triggerRelay(false);
    }

    if (stjorn.isPressed(FS_RELAY)){
        if (fs.duration() >= MIC_PRESS){
            triggerRelay(true);
        }
    }

}

void triggerRelay(bool state){
    
    if (state){
        digitalWrite(PIN_RELAY,HIGH);
    } else {
        digitalWrite(PIN_RELAY,LOW);
    }

}