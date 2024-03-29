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

/* ------------ STATE - LOOP --------------
 *  Functions for controlling Looper
 *  ---------------------------------------- */

#include <Bounce2.h>
#include "STJORN_definitions.h"
#include "STJORN_stateClass.h"
#include "STJORN_stateLoop.h"
#include "STJORN_micSwitcher.h"
#include "STJORN_footswitches.h"
#include "STJORN_display.h"

#define LOOP_CC_REC 51
#define LOOP_CC_PLAY 52
#define LOOP_CC_DUB 53
#define LOOP_CC_STOP 54
#define LOOP_CC_UNDO 55
#define LOOP_CC_CLEAR 56
#define LOOP_CC_DBL 57
#define LOOP_CC_HALF 58
#define LOOP_CC_FBINC 59
#define LOOP_CC_FBDEC 60
#define LOOP_CC_FBRESET 61
#define LOOP_CC_FADE 62

void stateLoop(Bounce *fs)
{

    // Process footswitch inputs
    for (int i = 0; i < NUM_FS; i++)
    {
        procFsLoop(fs[i], i);
    }

    procExprLoop();

    procLedLoop();

    procDisplayLoop();

    // reset 'changed' state flag if just changed to this state
    stjorn.confirmState(ST_LOOP);
}

void procFsLoop(Bounce fs, int fsNum)
{

    int press = 0;
    switch (fsNum)
    {
    case FS_ACT_MN ... FS_ACT_MX:
        press = fsShortLong(fs, fsNum); // returns PRESS_SHORT or PRESS_LONG
        if (press != NOT_PRESSED)
        {
            procLoopControl(fsNum, press);
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
        if (fs.fell())
        {
            stjorn.setState(ST_PATCH);
        }
        break;

    case FS_ST_LOOP:

        break;

    case FS_ST_NEXT:
        press = fsShortLong(fs, fsNum);
        if (press != NOT_PRESSED)
        {
            stjorn.setNext(press, -1);
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

void procLoopControl(int fsNum, int press)
{
    int cc = -1;
    bool clear = false;

    switch (fsNum)
    {
    case 0: // FDBK +
        if (press == PRESS_SHORT)
        {
            cc = LOOP_CC_FBINC;
        }
        else
        {
            cc = LOOP_CC_FBRESET;
        }
        clear = true;
        break;

    case 1: // LENGTH +
        cc = LOOP_CC_DBL;
        break;

    case 2: // UNDO
        cc = LOOP_CC_UNDO;
        break;

    case 3: // EXPR GTR
        if (stjorn.exprType() != EXPR_LOOP_CC)
        {
            stjorn.setExprType(EXPR_LOOP_CC);
        }
        else
        {
            stjorn.setExprType(EXPR_GTR_CC);
        }
        break;

    case 4: // FDBK -
        if (press == PRESS_SHORT)
        {
            cc = LOOP_CC_FBDEC;
        }
        else
        {
            cc = LOOP_CC_FBRESET;
        }
        clear = true;
        break;

    case 5: // LENGTH -
        cc = LOOP_CC_HALF;
        break;

    case 6: // STOP/CLR
        if (stjorn.looper() != LOOPER_STOP)
        { // looper playing/recording
            if (press == PRESS_SHORT)
            {
                cc = LOOP_CC_STOP;
            }
            else
            {
                cc = LOOP_CC_FADE;
            }
        }
        else
        { // looper stopped
            cc = LOOP_CC_CLEAR;
        }
        break;

    case 7: // REC/PLAY/DUB
        switch (stjorn.looper())
        {
        case LOOPER_STOP:
            if (press == PRESS_SHORT)
            {
                cc = LOOP_CC_REC;
            }
            else
            {
                cc = LOOP_CC_PLAY;
            }
            break;

        case LOOPER_RECORD:
            cc = LOOP_CC_DUB; // change this to menu/max/osc configurable
            break;

        case LOOPER_PLAY:
            cc = LOOP_CC_DUB;
            break;

        case LOOPER_OVERDUB:
            cc = LOOP_CC_PLAY;
            break;
        }
        break;

    default:

        break;
    }

    if (cc != -1)
    {
        usbMIDI.sendControlChange(cc, 127, MIDI_CH_LIVE);
        if (clear == true)
        {
            usbMIDI.sendControlChange(cc, 0, MIDI_CH_LIVE); // makes trigger momentary
        }
    }
}

void procExprLoop()
{

    if (stjorn.stateChange() == true)
    {                                    // state is newly entered
        stjorn.setExprType(EXPR_GTR_CC); // set to guitar CC on entering state
    }

    sendExpression();
}

void procLedLoop()
{

    for (int i = 0; i < NUM_ACTION; i++)
    {
        bool state = false;
        int color;
        switch (i)
        {
        case 0 ... 2:
            color = DARK;
            break;

        case 3:
            color = PINK;
            if (stjorn.exprType() == EXPR_LOOP_CC)
            {
                state = true;
            }
            else
            {
                state = false;
            }
            break;
        case 4 ... 5:
            color = DARK;
            break;
        case 6:
            if (stjorn.looper() == LOOPER_STOP)
            { // looper is stopped
                color = WHITE;
            }
            else
            { // looper is playing/recording
                color = RED;
            }
            state = true;
            break;
        case 7:
            switch (stjorn.looper())
            {
            case LOOPER_STOP:
                color = RED;
                break;
            case LOOPER_RECORD ... LOOPER_PLAY:
                color = CYAN;
                break;
            case LOOPER_OVERDUB:
                color = YELLOW;
                break;
            default:
                color = DARK;
                break;
            }
            state = true;
            break;
        }
        stjorn.setLed(ACTION, i, state, color);
    }
}

void procDisplayLoop()
{
    setDisplayMain();
}

void procLoopStateled()
{
    int color;
    int state;

    switch (stjorn.looper())
    {
    case LOOPER_STOP:
        color = DARK;
        state = false;
        break;

    case LOOPER_RECORD:
        color = RED;
        state = true;
        break;

    case LOOPER_PLAY:
        color = YELLOW;
        state = true;
        break;

    case LOOPER_OVERDUB:
        color = CYAN;
        state = true;
        break;

    default:
        color = DARK;
        state = false;
        break;
    }

    stjorn.setLed(STATE, LED_LOOP, state, color);
}
