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
#include "STJORN_stateFX.h"
#include "STJORN_micSwitcher.h"
#include "STJORN_footswitches.h"

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



}


void procFsFX(Bounce fs, int fsNum){

    int note = -1;
    int ch = 1;

    switch (fsNum){
        case FS_ACT_MN ... FS_ACT_MX:
            if (fs.fell() ){
                if (fsNum == FX_TAP) {
                    stjorn.sendTap();
                } else {
                    ch = MIDI_CH_GP;
                    note = fsNum + 17;
                }
            }
            break;

        case FS_ST_SONG:

            break;

        case FS_ST_RIG:
            int press = 0;
            press = fsShortLong(fs, fsNum);
            if (press == PRESS_SHORT){
                stjorn.setState(ST_PATCH);
            } else if (press == PRESS_LONG){
                stjorn.saveSongVar();
            }

            break;

        case FS_ST_LOOP:

            break;

        case FS_ST_NEXT:

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