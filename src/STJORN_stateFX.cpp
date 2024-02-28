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

/* ------------ STATE - FX --------------
 *  Functions for selecting FX and controlling state
 *  ---------------------------------------- */

#include <Bounce2.h>
#include "STJORN_definitions.h"
#include "STJORN_stateClass.h"
#include "STJORN_stateFX.h"
#include "STJORN_micSwitcher.h"
#include "STJORN_footswitches.h"
#include "STJORN_display.h"

void stateFX(Bounce *fs)
{

    // Process footswitch inputs
    for (int i = 0; i < NUM_FS; i++)
    {
        procFsFX(fs[i], i);
    }

    procExprFX();

    procLedFX();

    procDisplayFX();

    // reset 'changed' state flag if just changed to this state
    stjorn.confirmState(ST_FX);
}

void procFsFX(Bounce fs, int fsNum)
{

    int note = -1;
    int ch = MIDI_CH_GP;
    int press = 0;

    switch (fsNum)
    {
    case FX_MOD ... FX_VRB:
        if (fs.fell())
        {
            stjorn.setFXWetPage(fsNum + 1);
            stjorn.setState(ST_WETFX);
        }
        break;
    case FX_TAP ... FX_DR1:
        if (fsNum == FX_TAP)
        // TODO: Remove hold to engage
        {
            bool tapEngaged = fsTapEngage(fs, fsNum);
            if (tapEngaged)
            {
                if (fs.fell())
                {
                    stjorn.sendTap(true);
                }
                else if (fs.rose())
                {
                    stjorn.sendTap(false);
                }
            }
        }
        else
        {
            if (fs.fell())
            {
                note = fsNum + NOTE_FX1;
            }
        }
        break;

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

void procLedFX()
{

    // set FX LEDs
    // int fxLedCol[NUM_FX-1] = {BLUE, GREEN, ORANGE, WHITE, PINK, YELLOW, RED, RED}; // colour of each FX
    int fxLedCol[NUM_ACTION] = {I_BLUE, I_GREEN, I_ORANGE, I_WHITE, I_PINK, I_YELLOW, I_RED, I_RED}; // colour of each FX

    // Updated this to i < (NUM_FX -1) so that auxFX ([8]) is not included

    for (int i = 0; i < NUM_ACTION; i++)
    {
        int colour = DARK;
        bool fxState = false;
        if (i < 3) // Wet FX
        {
            switch (i + 1)
            {
            case TYPE_FX_MOD:
                fxState = stjorn.wet_fx_active(TYPE_FX_MOD - 1);
                break;
            case TYPE_FX_DLY:
                fxState = stjorn.wet_fx_active(TYPE_FX_DLY - 1);
                break;
            case TYPE_FX_VRB:
                fxState = stjorn.wet_fx_active(TYPE_FX_VRB - 1);
                break;
            }
        }
        else // Tap and all other FX
        {
            fxState = stjorn.fx(i);
        }

        if (fxState == true)
        {
            colour = fxLedCol[i];
        }

        int colour_led = setLedColour(colour, fxState);

        // state is always true for the LED to show dim colours
        stjorn.setLed(ACTION, i, true, colour_led);
    }

    // set next LED
    stjorn.setLed(NEXT, LED_NEXT, false, DARK);
}

void procDisplayFX()
{

    setDisplayMain();
}

void procExprFX()
{

    if (stjorn.exprType() != EXPR_GTR_CC)
    {
        stjorn.setExprType(EXPR_GTR_CC);
    }
    sendExpression();
}