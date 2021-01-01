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
    
}