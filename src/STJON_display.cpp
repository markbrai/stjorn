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

/* ------------ DISPLAY  --------------
*  Functions for setting display buffers
*  ---------------------------------------- */

#include <Arduino.h>
#include "STJORN_definitions.h"
#include "STJORN_stateClass.h"

void setDisplayPatch(){

    char dispPatch[NUM_PATCH][DIGIT_RIG] = {{'A','M'},
                                            {'R','2'},
                                            {'D','2'},
                                            {'L','2'},
                                            {'C','L'},
                                            {'R','1'},
                                            {'D','1'},
                                            {'L','1'}};

    if (stjorn.patch() == -1){
        stjorn.setDisplay(BLK_RIG,0,'-');
        stjorn.setDisplay(BLK_RIG,1,'-');
    } else {
        for (int i=0; i < DIGIT_RIG; i++){
            char ascii = dispPatch[stjorn.patch()][i];
            stjorn.setDisplay(BLK_RIG,i,ascii);
        }
    }
    
}

void setDisplaySong(){

}

void setDisplayCurr(){

}

void setDisplayNext(){
    
}