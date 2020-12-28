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

/* ------------ STATE - PATCH --------------
*  Functions for selecting patches and controlling state
*  ---------------------------------------- */

#include <Bounce2.h>
#include "STJORN_definitions.h"
#include "STJORN_stateClass.h"
#include "STJORN_statePatch.h"
#include "STJORN_micSwitcher.h"
#include "STJORN_footswitches.h"
#include "STJORN_display.h"

#define AM 0
#define R2 1
#define D2 2
#define L2 3
#define CL 4
#define R1 5
#define D1 6
#define L1 7


void statePatch(Bounce *fs){

    // Process footswitch inputs
    for (int i = 0; i < NUM_FS; i++){
        procFsPatch(fs[i], i);
    }

    procExprPatch();

    procLedPatch();

    procDisplayPatch();

    // reset 'changed' state flag if just changed to this state
    stjorn.confirmState(ST_PATCH);

}


void procFsPatch(Bounce fs, int fsNum){

    int note = -1;
    int ch = 1;
    int press = 0;

    switch (fsNum){
        case FS_ACT_MN ... FS_ACT_MX:
    
            ch = MIDI_CH_GP;
            if (fs.fell() && stjorn.patch() != fsNum){
                note = fsNum + 1;
                stjorn.selectPatch(fsNum);
            } else if (fs.fell() && stjorn.patch() == fsNum){
                note = stjorn.auxFX();
                //stjorn.setAux();
            }
            break;

        case FS_ST_SONG:
            if (fs.fell() ){
                stjorn.setState(ST_SONG);
            }
            break;

        case FS_ST_RIG:
            press = fsShortLong(fs, fsNum);
            if (press == PRESS_SHORT){
                stjorn.setState(ST_FX);
            } else if (press == PRESS_LONG){

            }
            break;

        case FS_ST_LOOP:
            if (fs.fell() ){
                stjorn.setState(ST_LOOP);
            }
            break;

        case FS_ST_NEXT:
            press = fsShortLong(fs, fsNum);
            if (press != NOT_PRESSED ){
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

    if (note != -1){
        usbMIDI.sendNoteOn(note,127,ch);
    }

}

void procLedPatch(){
int colour = PURPLE;

    // selected patch LED
    for (int i=0; i < NUM_PATCH; i++){
        bool state = false;
        if (stjorn.patch() == i){
            state = true;
        }
        if (stjorn.aux() ){
            colour = BLUE;
        }
        stjorn.setLed(ACTION,i,state,colour);
    }

    // next LED
    stjorn.setLed(NEXT,LED_NEXT,false,DARK);


}

void procDisplayPatch(){

    setDisplayMain();


}

void procExprPatch(){

    if (stjorn.exprType() != EXPR_GTR_CC){
        stjorn.setExprType(EXPR_GTR_CC);
    }
    sendExpression();
    
}