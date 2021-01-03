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

    // set state LED to starting state
    setLed(STATE,getStateLed(m_stCurr),true,m_stLedCol[m_stCurr]);    // intialise state LED

    // set song number to initial (01)
    setSongDigits(m_currSong);

}

// SET FUNCTIONS *********************

void Stjorn::setState(int stNew)
{
    m_stPrev = m_stCurr;
        setLed(STATE,getStateLed(m_stPrev),false,DARK);
    m_stCurr = stNew;
        setLed(STATE,getStateLed(m_stCurr),true,m_stLedCol[m_stCurr]);
    m_stChange = true;

    if (m_stCurr == ST_SONG){
        m_songPage = false;     // reset song page
    }

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

void Stjorn::setAux()
{
    m_aux = !m_aux;
    if (!m_auxPressed){
        m_auxPressed = true;
    }

}

void Stjorn::setAux(bool state)
{
    m_aux = state;
    m_auxPressed = state;
}

void Stjorn::setAuxFX(int aux)
{
    m_fxAux = aux;
}

void Stjorn::sendTap(bool state)
{ int ccVal = 0;

    if (state){
        ccVal = 127;
    }

    usbMIDI.sendControlChange(LIVE_TAP,ccVal,MIDI_CH_LIVE);
}

void Stjorn::saveSongVar()
{
    usbMIDI.sendControlChange(1,127,MIDI_CH_GP);
}

void Stjorn::setSong(int song)
{
    m_currSong = song;
    setSongDigits(m_currSong);
}

void Stjorn::setSong(int press, int song)
{
    m_currSong = song;
    setSongDigits(m_currSong);
    sendSong(press, m_currSong);
}

void Stjorn::setNext(int press, int song)
{
    if (m_nextSong == false){
        if (song == -1) {            // triggered from 'next'
            setSong(m_currSong + 1);
        } else {
            setSong(song);
        }
    }

    sendSong(press,m_currSong);

}

void Stjorn::setSongPage(bool page)
{
    m_songPage = page;
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

void Stjorn::setTap(bool state)
{
    m_tap = state;
    m_fx[FX_TAP] = m_tap;
}


void Stjorn::setLooper(int state)
{
    m_looperState = state;
}

void Stjorn::setExprType(int type)
{
    m_exprType = type;
}

void Stjorn::setScenes(int byteNum, byte charVal)
{ int idx = 0;

    if (byteNum > SYS_BYTE_CURR){
        switch (byteNum){
            case SYS_BYTE_CURR ... SYS_BYTE_CURR+3:
                idx = byteNum - SYS_BYTE_CURR;
                m_sceneCurr[idx] = charVal;
                break;
            case SYS_BYTE_G1 ... SYS_BYTE_G1+3:
                idx = byteNum - SYS_BYTE_G1;
                m_sceneGoto1[idx] = charVal;
                break;
            case SYS_BYTE_G2 ... SYS_BYTE_G2+3:
                idx = byteNum - SYS_BYTE_G2;
                m_sceneGoto2[idx] = charVal;
                break;
            case SYS_BYTE_G3 ... SYS_BYTE_G3+3:
                idx = byteNum - SYS_BYTE_G3;
                m_sceneGoto3[idx] = charVal;
                break;
            case SYS_BYTE_G4 ... SYS_BYTE_G4+3:
                idx = byteNum - SYS_BYTE_G4;
                m_sceneGoto4[idx] = charVal;
                break;
            case SYS_BYTE_NEXT ... SYS_BYTE_NEXT+3:
                idx = byteNum - SYS_BYTE_NEXT;
                m_sceneNext[idx] = charVal;
                break;
            default:
                break;

        }
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

char Stjorn::songDigit(int digit){
/*char _m_songDigit;

    _m_songDigit = m_songDigits[digit];

    return _m_songDigit;*/

    return m_songDigits[digit];

}



// PRIVATE FUNCTIONS

int Stjorn::getStateLed(int state)
{

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

void Stjorn::setSongDigits(int song)
{
    int _m_songDisplay = song + 1;
    int _m_digit = _m_songDisplay % 10;     // get lowest digit
    m_songDigits[1] = _m_digit + '0';
    //setDisplay(BLK_SONG,1,_m_digit + '0');
    _m_songDisplay /= 10;    // remove lowest digit
    _m_digit = _m_songDisplay % 10;     // get digit
    m_songDigits[0] = _m_digit + '0';
    //setDisplay(BLK_SONG,0,_m_digit + '0');

}

void Stjorn::sendSong(int press, int song){

    if (press == PRESS_SHORT){
        if (m_nextSong == false){        // immediate next GP & LIVE
            usbMIDI.sendProgramChange(m_currSong,MIDI_CH_LIVE);
            usbMIDI.sendProgramChange(m_currSong,2);
        } else {                        // next GP
            usbMIDI.sendProgramChange(m_currSong,2);
            m_nextSong = false;
        }
    } else if (press == PRESS_LONG){    // next LIVE only
        usbMIDI.sendProgramChange(m_currSong,MIDI_CH_LIVE);
        m_nextSong = true;
    }
}