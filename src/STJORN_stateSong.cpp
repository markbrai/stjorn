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

/* ------------ STATE - SONG --------------
*  Functions for selecting songs and controlling state
*  ---------------------------------------- */

#include <Bounce2.h>
#include "STJORN_definitions.h"
#include "STJORN_stateClass.h"
#include "STJORN_stateSong.h"
#include "STJORN_micSwitcher.h"
#include "STJORN_footswitches.h"
#include "STJORN_display.h"

void stateSong(Bounce *fs){

    for (int i = 0; i < NUM_FS; i++){
        procFsSong(fs[i], i);
    }

    procExprSong();

    procLedSong();

    procDisplaySong();

   // reset 'changed' state flag if just changed to this state
    stjorn.confirmState(ST_SONG);    

}

void procFsSong(Bounce fs, int fsNum){

    int press = 0;

    switch (fsNum){
        case FS_ACT_MN ... FS_ACT_MX:
            press = fsShortLong(fs, fsNum);
            if (press != 0){
                stjorn.setSong(press,fsNum);
            }
            break;

        case FS_ST_SONG:
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
            if (press != 0 ){
                stjorn.setNext(press, -1);
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

void procExprSong(){
    sendExpression(EXPR_GTR_CC,MIDI_CH_GP);
}

void procLedSong(){
int colour = WHITE;

    for (int i = 0; i < NUM_ACTION; i++){
        bool state = false;
        if (stjorn.song()== i){
            state = true;
        }
        stjorn.setLed(ACTION,i,state,colour);
    }


}

void procDisplaySong(){
    setDisplayMain();
}