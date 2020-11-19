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

/* ------------ STATE CLASS --------------
*  Main class to hold all STJORN data to pass between states
*  ---------------------------------------- */

#include <Arduino.h>
#include "STJORN_definitions.h"
#include "STJORN_stateClass.h"
#include "STJORN_definitions.h"

int ledNum;

// CONSTRUCTOR *********************

Stjorn::Stjorn()
{
    // initialise both states to 0
    m_stCurr = ST_PATCH;        
    m_stPrev = ST_PATCH;
    // set state LED
    setLed(STATE,getStateLed(m_stCurr),true,m_stLedCol[m_stCurr]);    // intialise state LED

    
}

// SET FUNCTIONS *********************

void Stjorn::setState(int stNew)
{
    m_stPrev = m_stCurr;
        setLed(STATE,getStateLed(m_stPrev),false,DARK);
    m_stCurr = stNew;
        setLed(STATE,getStateLed(m_stCurr),true,m_stLedCol[m_stCurr]);
    m_stChange = true;

}

void Stjorn::confirmState(int state)
{
    if (m_stChange == true && state == m_stCurr){
        m_stChange = false;          // return true to set LED
    }

}

void Stjorn::setPressed(int btn, bool state)
{
    m_pressed[btn] = state;
}

void Stjorn::setLed(int type, int num, bool state, int colour)
{
    int led = -1;

    switch (type){
        case ACTION:
            led = m_ledNumAction[num];
            break;
        case STATE:
            led = num;
            break;
        case NEXT:
            led = num;
            break;
        case MIC:
            led = num;
            break;
        case TRANSPORT:
            led = num;
            break;
        default:
            break;
    }


    m_ledState[led] = state;
    m_ledColour[led] = colour;
}


void Stjorn::selectPatch(int patch)
{
    m_patchSelected = patch;
}

void Stjorn::setRelay(int state)
{
    m_relayState = state;
}

void Stjorn::setFX(int fx, bool state)
{
    m_fx[fx] = state;
}

void Stjorn::sendTap()
{
    usbMIDI.sendControlChange(LIVE_TAP,127,MIDI_CH_LIVE);
}

void Stjorn::saveSongVar()
{
    usbMIDI.sendControlChange(1,127,MIDI_CH_GP);
}

void Stjorn::setSong(int song)
{
    m_currSong = song;
}

void Stjorn::setNext(int press, int song)
{
    if (song == -1){            // triggered from 'next'
        song = m_currSong + 1;
    }

    if (press == PRESS_SHORT){
        if (m_nextSong == false){        // immediate next GP & LIVE
            usbMIDI.sendProgramChange(song,MIDI_CH_LIVE);
            usbMIDI.sendProgramChange(song,MIDI_CH_GP);
        } else {                        // next GP
            usbMIDI.sendProgramChange(song,MIDI_CH_GP);
            m_nextSong = false;
        }
    } else if (press == PRESS_LONG){    // next LIVE only
        usbMIDI.sendProgramChange(song,MIDI_CH_LIVE);
        m_nextSong = true;
    }
}

void Stjorn::setDisplay(int block, int digit, char ascii)
{
    switch (block){
        case BLK_SONG:
            m_dispSong[digit] = ascii;
            break;
        case BLK_CURR:
            m_dispCurr[digit] = ascii;
            break;
        case BLK_NEXT:
            m_dispNext[digit] = ascii;
            break;
        case BLK_RIG:
            m_dispRig[digit] = ascii;
            break;
        default:
            break;
    }
}

void Stjorn::setProx(int prox)
{
    if (prox == m_exprProxPrev){
        m_exprChanged = false;
    } else {
        m_exprProxPrev = m_exprProx;
        m_exprProx = prox;
        m_exprChanged = true;
    }
}


// GET FUNCTIONS *********************

bool Stjorn::isPressed(int btn)
{
    return m_pressed[btn];
}

bool Stjorn::isLit(int led)
{
    return m_ledState[led];
}

int Stjorn::isColour(int led)
{
    return m_ledColour[led];
}

bool Stjorn::fx(int fx)
{
    return m_fx[fx];
}

char Stjorn::ascii(int blk, int digit)
{
    char ascii = ' ';

    switch (blk){
        case BLK_SONG:
            ascii = m_dispSong[digit];
            break;
        case BLK_CURR:
            ascii = m_dispCurr[digit];
            break;
        case BLK_NEXT:
            ascii = m_dispNext[digit];
            break;
        case BLK_RIG:
            ascii = m_dispRig[digit];
            break;
        default:
            break;
    }

    return ascii;
}




// PRIVATE FUNCTIONS

int Stjorn::getStateLed(int state){

    switch (state){
        case ST_TRACKS ... ST_SONG:
            ledNum = LED_SONG;
            break;
        case ST_PATCH ... ST_FX:
            ledNum = LED_RIG;
            break;
        case ST_LOOP ... ST_PADS:
            ledNum = LED_LOOP;
            break;
        default:
            break;
    }

    return ledNum;

}