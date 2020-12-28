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

/* ------------ STATE - LOOP --------------
*  Functions for controlling Looper
*  ---------------------------------------- */

#include <Bounce2.h>
#include "STJORN_definitions.h"
#include "STJORN_stateClass.h"
#include "STJORN_stateLoop.h"
#include "STJORN_micSwitcher.h"
#include "STJORN_footswitches.h"
#include "STJORN_display.h"

void stateLoop(Bounce *fs){

    // Process footswitch inputs
    for (int i = 0; i < NUM_FS; i++){
        procFsLoop(fs[i],i);
    }

}

void procFsLoop(Bounce fs, int fsNum){

    int press = 0;

    switch (fsNum){
        case FS_ACT_MN ... FS_ACT_MX:


            break;
        
        case FS_ST_SONG:
            if (fs.fell() ){
                stjorn.setState(ST_SONG);
            }
            break;

        case FS_ST_RIG:
            if (fs.fell() ){
                stjorn.setState(ST_PATCH);
            }
            break;

        case FS_ST_LOOP:

            break;

        case FS_ST_NEXT:
            press = fsShortLong(fs, fsNum);
            if (press != 0) {
                stjorn.setNext(press,-1);
            }
            break;

        case FS_RELAY:
            processRelay(fs);
            break;

        case FS_OS_MN:

            break;

        case FS_OS_MX:

            break;
    }







}