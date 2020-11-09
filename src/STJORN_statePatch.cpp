#include <Bounce2.h>
#include "STJORN_definitions.h"
#include "STJORN_stateClass.h"
#include "STJORN_statePatch.h"

#define AM 0
#define R2 1
#define D2 2
#define L2 3
#define CL 4
#define R1 5
#define D1 6
#define L1 7


void statePatch(Bounce *fs){

    for (int i = 0; i < NUM_FS; i++){
        procFsPatch(fs[i], i);
    }

}


void procFsPatch(Bounce fs, int fsNum){

    int note = -1;
    int ch = 1;

    switch (fsNum){
        case FS_ACT_MN ... FS_ACT_MX:
    
            ch = MIDI_CH_GP;
            if (fs.fell() && stjorn.patch() != fsNum){
                note = fsNum + 1;
            } else if (fs.fell() && stjorn.patch() == fsNum){
                note = fsNum + 9;
            }
            break;

        case FS_ST_TRAX:

            break;

        case FS_ST_FX:

            break;

        case FS_ST_LOOP:

            break;

        case FS_ST_SONG:

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