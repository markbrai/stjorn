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

#ifndef STJORN_STATECLASS_H
#define STJORN_STATECLASS_H

#include <Arduino.h>
#include "STJORN_definitions.h"

class Stjorn
{
    private:
        int m_stCurr{};
        int m_stPrev{};
        bool m_pressed[NUM_FS];
        bool m_ledState[NUM_LEDS];
        int m_ledColour[NUM_LEDS];
        int m_patchSelected{-1};
        int m_relayState{OPEN};
        bool m_fx[7];
        int m_currSong{0};
        bool m_nextSong{-1};


    public:
        // constructor
        Stjorn();

        // Set functions
        void setState(int stNew);
        void setPressed(int btn, bool state);
        void setLed(int led, bool state, int colour);
        void selectPatch(int patch);
        void setRelay(int state);
        void setFX(int fx, bool state);
        void sendTap();
        void saveSongVar();
        void setNext(int press, int song);

        // Get functions
        int state() {return m_stCurr;}
        int prevState() {return m_stPrev;}
        bool isPressed(int btn);
        bool isLit(int led);
        int isColour(int led);
        int patch() {return m_patchSelected;}
        int relay() {return m_relayState;}
        bool fx(int fx);
        bool next() {return m_nextSong;}
};


extern Stjorn stjorn;

#endif