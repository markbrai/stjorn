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

/* ------------ TAP & CLICK --------------
*  Functions for controlling click and tap tempo footswitches
*  ---------------------------------------- */

#include <Bounce2.h>
#include "STJORN_definitions.h"
#include "STJORN_stateClass.h"
#include "STJORN_tapClick.h"
#include "STJORN_footswitches.h"


void processTap(Bounce fs){
    if (fs.fell())
    {
        stjorn.sendTap(true);
    }
    else if (fs.rose())
    {
        stjorn.sendTap(false);
    }
};

void processClick(Bounce fs){

    if (fs.fell()){
    usbMIDI.sendNoteOn(NOTE_CLICK, 127, MIDI_CH_GP);
    }

}