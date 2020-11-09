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

void updateFootswitches(Bounce *fs){

    for (int i=0; i < NUM_FS; i++){
        fs[i].update();
    }
}