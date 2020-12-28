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

    if (stjorn.stateChange() && stjorn.song() > 7){
        stjorn.setSongPage(true);
    }

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
            int _songNum;
            if (press != NOT_PRESSED){
                int _songNum;
                if (stjorn.songPage() ){
                    _songNum = fsNum + 8; 
                } else {
                    _songNum =fsNum;
                }
                stjorn.setSong(press,_songNum);
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
            if (fs.fell() ){
                stjorn.setState(ST_LOOP);
            }
            break;

        case FS_ST_NEXT:
            /*press = fsShortLong(fs, fsNum);
            if (press != 0 ){
                stjorn.setNext(press, -1);
            }*/
            if (fs.fell() ){
                stjorn.setSongPage(!stjorn.songPage() );
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
int colour = BLUE;

    // selected song LED
    for (int i = 0; i < NUM_ACTION; i++){
        bool state = false;
        if ((stjorn.song()== i && !stjorn.songPage() )
            || (stjorn.song()== i+8 && stjorn.songPage() ) ){
            state = true;
        }
        stjorn.setLed(ACTION,i,state,colour);
    }

    // page 2 LED
    stjorn.setLed(NEXT,LED_NEXT,stjorn.songPage(),BLUE);


}

void procDisplaySong(){
    setDisplayMain();
}