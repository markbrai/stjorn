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
    stjorn.confirmState(ST_FX);
}

void procFsWetFx(Bounce fs, int fsNum)
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