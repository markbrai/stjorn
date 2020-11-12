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