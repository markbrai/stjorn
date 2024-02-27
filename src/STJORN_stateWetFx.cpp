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
        if (fs.fell())
        {
            switch (stjorn.wet_fx_page())
            {
            case TYPE_FX_MOD:
                note = procWetFxMod(fsNum);
                break;
            case TYPE_FX_DLY:
                note = procWetFxDly(fsNum);
                break;
            case TYPE_FX_VRB:
                note = procWetFxVrb(fsNum);
                break;
            }
        }
        break;
    // bottom row
    case FX_FLT ... FX_DR1:
        if (fs.fell())
        {
            if (fsNum == FX_DR1)
            {
                // Exit back to FX page
                stjorn.setState(ST_FX);
            }
            else
            {
                // Change 'page' to specified wet fx
                stjorn.setFXWetPage(fsNum - 3);
            }
            break;
        }

    case FS_ST_SONG:
        if (fs.fell())
        {
            stjorn.setState(ST_TRACKS);
        }
        break;

    case FS_ST_RIG:
        // TODO: Move to function from _statePatch
        press = fsShortLong(fs, fsNum);
        if (press == PRESS_SHORT)
        {
            stjorn.setState(ST_PATCH);
        }
        else if (press == PRESS_LONG)
        {
        }

        break;

    case FS_ST_LOOP:
        if (fs.fell())
        {
            stjorn.setState(ST_LOOP);
        }
        break;

    case FS_ST_NEXT:
        press = fsShortLong(fs, fsNum);
        if (press != 0)
        {
            stjorn.setNext(press, -1);
        }

    case FS_RELAY:
        processRelay(fs);
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

int procWetFxFs(bool state, int fsNum, int noteAdd)
{
    int note;
    if (state == false)
    {
        // If 0 then send MIDI to turn on
        note = fsNum + noteAdd;
    }
    else
    {
        // if 1 then send MIDI to turn off
        note = noteAdd + 4;
    }

    return note;
}

int procWetFxMod(int fsNum)
{
    // Get fx array at fsNum index

    bool state = stjorn.fx_mod(fsNum);
    int note = procWetFxFs(state, fsNum, NOTE_FX_MOD_1);

    return note;
}

int procWetFxDly(int fsNum)
{

    bool state = stjorn.fx_dly(fsNum);
    int note = procWetFxFs(state, fsNum, NOTE_FX_DLY_1);

    return note;
}

int procWetFxVrb(int fsNum)
{
    bool state = stjorn.fx_vrb(fsNum);
    int note = procWetFxFs(state, fsNum, NOTE_FX_VRB_1);

    return note;
}

const int I_MOD_COLOUR = 4;
const int I_DLY_COLOUR = 5;
const int I_VRB_COLOUR = 6;
const int I_EXIT_COLOUR = 7;

void procLedWetFx()
{
    int led_color = DARK;
    switch (stjorn.wet_fx_page())
    {
    case TYPE_FX_MOD:
        led_color = I_BLUE;
        break;
    case TYPE_FX_DLY:
        led_color = I_GREEN;
        break;
    case TYPE_FX_VRB:
        led_color = I_ORANGE;
        break;
    }

    int fxLedCol[NUM_FX - 1] = {led_color, led_color, led_color, led_color, I_BLUE, I_GREEN, I_ORANGE, I_WHITE};
    for (int i = 0; i < NUM_FX - 1; i++)
    {
        int colour = I_DARK;
        bool wet_fx = false;
        if (i < 4)
        {

            switch (stjorn.wet_fx_page())
            {
            case TYPE_FX_MOD:
                wet_fx = stjorn.fx_mod(i);
                break;
            case TYPE_FX_DLY:
                wet_fx = stjorn.fx_dly(i);
                break;
            case TYPE_FX_VRB:
                wet_fx = stjorn.fx_vrb(i);
                break;
            }
            if (wet_fx == true)
            {
                colour = fxLedCol[i];
            }
        }
        else
        {
            switch (i)
            {
            case I_MOD_COLOUR:
                if (stjorn.wet_fx_page() == TYPE_FX_MOD)
                {
                    wet_fx = true;
                }
                break;
            case I_DLY_COLOUR:
                if (stjorn.wet_fx_page() == TYPE_FX_DLY)
                {
                    wet_fx = true;
                }
                break;
            case I_VRB_COLOUR:
                if (stjorn.wet_fx_page() == TYPE_FX_VRB)
                {
                    wet_fx = true;
                }
                break;
            case I_EXIT_COLOUR:
                wet_fx = true;
                break;
            }
            colour = fxLedCol[i];
        }

        int colour_led = setLedColour(colour, wet_fx);
        stjorn.setLed(ACTION, i, true, colour);
    }

    stjorn.setLed(NEXT, LED_NEXT, false, DARK);
}

void procDisplayWetFx()
{
    setDisplayMain();
}

void procExprWetFx()
{
}