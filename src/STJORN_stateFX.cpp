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

/* ------------ STATE - FX --------------
*  Functions for selecting FX and controlling state
*  ---------------------------------------- */

#include <Bounce2.h>
#include "STJORN_definitions.h"
#include "STJORN_stateClass.h"
#include "STJORN_stateFX.h"
#include "STJORN_micSwitcher.h"
#include "STJORN_footswitches.h"
#include "STJORN_display.h"

#define FX_MOD 0
#define FX_DLY 1
#define FX_VRB 2
#define FX_TAP 3
#define FX_FLT 4
#define FX_CMP 5
#define FX_DR2 6
#define FX_DR1 7


void stateFX(Bounce *fs){

    // Process footswitch inputs
    for (int i = 0; i < NUM_FS; i++){
        procFsFX(fs[i], i);
    }

    procExprFX();

    procLedFX();

    procDisplayFX();



    // reset 'changed' state flag if just changed to this state
    stjorn.confirmState(ST_FX);

}


void procFsFX(Bounce fs, int fsNum){

    int note = -1;
    int ch = MIDI_CH_GP;
    int press = 0;

    switch (fsNum){
        case FX_MOD ...  FX_VRB:
            press = fsShortLong(fs,fsNum);
            if (press == PRESS_SHORT){
                note = fsNum + 17; 
            } else if (press == PRESS_LONG){
                note = fsNum + 25;
            }
            break;
        case FX_TAP ... FS_ACT_MX:
            if (fsNum == FX_TAP) {
                bool tapEngage = fsTapEngage(fs,fsNum);
                if (tapEngage){
                    stjorn.sendTap();
                }
            } else {
                if (fs.fell() ){
                    note = fsNum + 17;
                }
            }
            break;

        case FS_ST_SONG:
            /*if (fs.fell() ){
                stjorn.setState(ST_TRACKS);
            }*/
            break;

        case FS_ST_RIG:
            press = fsShortLong(fs, fsNum);
            if (press == PRESS_SHORT){
                stjorn.setState(ST_PATCH);
            } else if (press == PRESS_LONG){

            }

            break;

        case FS_ST_LOOP:
            /*if (fs.fell() ){
                stjorn.setState(ST_LOOP);
            }*/
            break;

        case FS_ST_NEXT:
            press = 0;
            press = fsShortLong(fs, fsNum);
            stjorn.setNext(press, -1);
            break;

        case FS_RELAY:
            processRelay(fs);
            break;
        
        case FS_OS_MN:

            break;

        case FS_OS_MX:

            break;
    }

    if (note != -1){
        usbMIDI.sendNoteOn(note,127,ch);
    }

}

void procLedFX(){

    int fxLedCol[NUM_FX] = {BLUE,GREEN,ORANGE,DARK,PINK,YELLOW,RED,RED}; // colour of each FX

    for (int i = 0; i < NUM_FX; i++){
        int colour = DARK;
        if (stjorn.fx(i) == true){
            colour = fxLedCol[i];
        } 
        stjorn.setLed(ACTION,i,stjorn.fx(i),colour);
    }

}

void procDisplayFX(){

    setDisplayPatch();

}

void procExprFX(){

    sendExpression(EXPR_GTR_CC,MIDI_CH_GP);


}