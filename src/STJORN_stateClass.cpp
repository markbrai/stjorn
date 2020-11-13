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

// CONSTRUCTOR *********************

Stjorn::Stjorn()
{
    // initialise both states to 0
    m_stCurr = ST_PATCH;        
    m_stPrev = ST_PATCH;
}

// SET FUNCTIONS *********************

void Stjorn::setState(int stNew)
{
    m_stPrev = m_stCurr;
    m_stCurr = stNew;
    m_stChange = true;
}

void Stjorn::confirmState(int state)
{
    if (m_stChange == true && state == m_stCurr){
        m_stChange = false;
    }
}

void Stjorn::setPressed(int btn, bool state)
{
    m_pressed[btn] = state;
}

void Stjorn::setLed(int led, bool state, int colour)
{
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
