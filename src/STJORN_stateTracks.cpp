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

/* ------------ STATE - TRACKS --------------
*  Functions for controlling Ableton Live Tracks
*  ---------------------------------------- */

#include <Bounce2.h>
#include "STJORN_definitions.h"
#include "STJORN_stateClass.h"
#include "STJORN_stateTracks.h"
#include "STJORN_micSwitcher.h"
#include "STJORN_footswitches.h"
#include "STJORN_display.h"

#define CC_NUM 0
#define CC_VAL 1

#define FS_STOP 0
#define FS_PLAY 1
#define FS_CYCLE 2
#define FS_TAP 3
#define FS_G4 4
#define FS_G3 5
#define FS_G2 6
#define FS_G1 7

void stateTracks(Bounce *fs) {

    for (int i = 0; i < NUM_FS; i++) {
        procFsTracks(fs[i],i);
    }

    procExprTracks();

    procLedTracks();

    procDisplayTracks();

    // reset 'changed' state flag if just changed to this state
    stjorn.confirmState(ST_TRACKS);

}

void procFsTracks(Bounce fs, int fsNum) {

int press = 0;
int arrCC[2] = {-1,0};

    switch (fsNum){
        case FS_ACT_MN ... FS_ACT_MX:
            if (fsNum == FS_TAP){
                bool tapEngaged = fsTapEngage(fs, fsNum);
                if (tapEngaged){
                    if (fs.fell() ){
                        stjorn.sendTap(true);
                    } else if (fs.rose() ){
                        stjorn.sendTap(false);
                    }
                }
            } else {
                tracksControls(arrCC,fsNum,fs);
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
            if (fs.fell() ){
                stjorn.setState(ST_LOOP);
            }
            break;

        case FS_ST_NEXT:
            press = fsShortLong(fs, fsNum);
            if (press != NOT_PRESSED){
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

    if (arrCC[CC_NUM] != -1){
        usbMIDI.sendControlChange(arrCC[CC_NUM],arrCC[CC_VAL],MIDI_CH_LIVE);
    }
    
}

void tracksControls(int arrCC[2], int fsNum, Bounce fs){
 #define BOTH 1
 #define SHORT 0
 #define NONE -1
 
 int press = 0;
 int arrFsShortLong[8] = {BOTH,BOTH,BOTH,SHORT,SHORT,SHORT,SHORT,SHORT};
 int arrCCNumShort[8] = {CC_STOP,CC_TRANSPORT,CC_CYCLETOG,NONE,CC_GOTO4,CC_GOTO3,CC_GOTO2,CC_GOTO1};
 int arrCCValShort[8] = {CC_VAL_STOP_OUT,CC_VAL_PLAY,CC_VAL_CYCTOG,NONE,CC_VAL_GOTO,CC_VAL_GOTO,CC_VAL_GOTO,CC_VAL_GOTO};
 int arrCCNumLong[8] = {CC_STOP,CC_TRANSPORT,CC_CUEMUTE,NONE,NONE,NONE,NONE,NONE};
 int arrCCValLong[8] = {CC_VAL_SOFTSTOP,CC_VAL_CLICK,CC_VAL_CUE_MUTE,NONE,NONE,NONE,NONE,NONE};

    if (arrFsShortLong[fsNum] == 0){
        if (fs.fell() ){
            arrCC[CC_NUM] = arrCCNumShort[fsNum];
            arrCC[CC_VAL] = arrCCValShort[fsNum];
        }
    } else {
        press = fsShortLong(fs,fsNum);
        if (press == PRESS_SHORT){
            arrCC[CC_NUM] = arrCCNumShort[fsNum];
            arrCC[CC_VAL] = arrCCValShort[fsNum];
        } else if (press == PRESS_LONG){
            arrCC[CC_NUM] = arrCCNumLong[fsNum];
            arrCC[CC_VAL] = arrCCValLong[fsNum];
        }
    }

}


void procExprTracks(){

    if (stjorn.exprType() != EXPR_GTR_CC){
        stjorn.setExprType(EXPR_GTR_CC);
    }
    sendExpression();

}

void procLedTracks(){

    for (int i = 0; i < NUM_ACTION; i++){
    int colour = DARK;
    int state = false;
        switch (i){
            case 0:         // stop
                if (stjorn.transport() != TRAN_STOP){
                    state = true;
                    colour = RED;
                }
                break;
            case 1:         // play
                if (stjorn.transport() != TRAN_PLAY){
                    state = true;
                    colour = GREEN;
                }
                break;
            case 2:         // cycle
                if (stjorn.transport() != TRAN_STOP){
                    state = true;
                    colour = YELLOW;
                }
                break;
            case 3:         // tap
                state = stjorn.fx(i);
                colour = WHITE;
                break;
            case 4 ... 7:         // goto 4
                if (stjorn.transport() != TRAN_STOP){
                    state = true;
                    colour = PURPLE;
                }
                break;
            default:
                break;
        }
    stjorn.setLed(ACTION,i,state,colour);

    }



}

void procDisplayTracks(){

    setDisplayMain();

}