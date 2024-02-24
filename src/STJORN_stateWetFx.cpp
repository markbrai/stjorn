/* ------------ STJORN controller --------------
 *  Code written for Teensy 3.2 micro-controller
 *  Teensy USB Type should be set to 'MIDI'
 *
 * https://github.com/markbrai/stjorn
 * https://hackaday.io/project/162616-stjrn
 *
 * https://www.gigperformer.com
 *
 * Mark Braithwaite, 2024
 *
 */

/* ------------ STATE - FX --------------
 *  Functions for selecting  Wet FX and controlling state
 *  ---------------------------------------- */

#include <Bounce2.h>
#include "STJORN_definitions.h"
#include "STJORN_stateClass.h"
#include "STJORN_stateWetFx.h"
#include "STJORN_micSwitcher.h"
#include "STJORN_footswitches.h"
#include "STJORN_display.h"

void stateWetFx(Bounce *fs)
{
    // Process footswitch inputs
    for (int i = 0; i < NUM_FS; i++)
    {
        procFsWetFx(fs[i], i);
    }

    procExprWetFx();

    procLedWetFx();

    procDisplayWetFx();

    // reset 'changed' state flag if just changed to this state
    stjorn.confirmState(ST_WETFX);
}

void procFsWetFx(Bounce fs, int fsNum)
{
    int note = -1;
    int ch = MIDI_CH_GP;
    int press = 0;

    switch (fsNum)
    {
    // Top row buttons
    case FX_MOD ... FX_TAP:
        /*
        - If not already active, send MIDI to activate
        - If already active, send MIDI to switch off
        - Different MIDI for Mod, Delay, Verb
        */
       if (fs.fell()){
        switch (stjorn.wet_fx_page())
        {
            case TYPE_FX_MOD:
                procWetFxMod(fsNum);
                break;
            case TYPE_FX_DLY:
                procWetFxDly(fsNum);
                break;
            case TYPE_FX_VRB:
                procWetFxVrb(fsNum);
                break;
        }
       }
        break;
    // bottom row
    case FX_FLT ... FX_DR1:
        break;
    case FS_ST_SONG:
        break;
    case FS_ST_RIG:
        break;
    case FS_ST_LOOP:
        break;
    case FS_RELAY:
        break;
    case FS_OS_MN:
        break;
    case FS_OS_MX:
        break;
    }

    if (note != -1)
    {
        usbMIDI.sendNoteOn(note, 127, ch);
    }
}

void procWetFxMod(int fsNum)
{
    // Get fx array at fsNum index

    if (stjorn.fx_mod(fsNum) == false) {
    // If 0 then send MIDI to turn on

    } else {
    // if 1 then send MIDI to turn off
    }

}

void procWetFxDly(int fsNum)
{

}

void procWetFxVrb(int fsNUm)
{

}

void procLedWetFx()
{
}

void procDisplayWetFx()
{
}

void procExprWetFx()
{
}