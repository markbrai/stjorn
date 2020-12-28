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

#define LOOP_REC 51
#define LOOP_PLAY 52
#define LOOP_DUB 53
#define LOOP_STOP 54
#define LOOP_UNDO 55
#define LOOP_CLEAR 56
#define LOOP_DBL 57
#define LOOP_HALF 58
#define LOOP_FBINC 59
#define LOOP_FBDEC 60
#define LOOP_FBRESET 61




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
            press = fsShortLong(fs, fsNum);     // returns PRESS_SHORT or PRESS_LONG
            if (press != NOT_PRESSED)  {
                procLoopControl(fsNum, press);
            }

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
            if (press != NOT_PRESSED) {
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

        default:
            break;
    }

}


void procLoopControl(int fsNum, int pressLong){

    switch (fsNum){
        case 0:     // FDBK +

            break;

        case 1:     // LENGTH +

            break;

        case 2:     // UNDO

            break;

        case 3:     // EXPR GTR

            break;
        
        case 4:     // FDBK -

            break;

        case 5:     // LENGTH -

            break;
        
        case 6:     // STOP/CLR

            break;

        case 7:     // REC/PLAY

            break;

        default:
            break;
        

    }



}

