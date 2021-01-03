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
#include "STJORN_display.h"

void setDisplayMain(){
    setDisplayPatch();
    setDisplaySong();
    setDisplayCurr();
    setDisplayNext();
}

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

for (int i = 0; i < DIGIT_SONG; i++){
    stjorn.setDisplay(BLK_SONG,i,stjorn.songDigit(i));
}    


}

void setDisplayCurr(){
char ascii;

    for (int i = 0; i < DIGIT_CURR; i++){
        ascii = stjorn.scene(SCENE_CURR,i);
        stjorn.setDisplay(BLK_CURR,i,ascii);
    }

}

void setDisplayNext(){
char ascii;

    for (int i = 0; i <DIGIT_CURR; i++){
        ascii = stjorn.scene(SCENE_NEXT,i);
        stjorn.setDisplay(BLK_NEXT,i,ascii);
    }
    
}