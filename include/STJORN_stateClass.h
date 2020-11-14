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
        // state 
        int m_stCurr{};
        int m_stPrev{};
        bool m_stChange{false};
        int m_stLedCol[NUM_STATES] = {WHITE,BLUE,WHITE,BLUE,WHITE,BLUE};
        int getStateLed(int state);
        // footswitch 
        bool m_pressed[NUM_FS];
        // leds
        bool m_ledState[NUM_LEDS];
        int m_ledColour[NUM_LEDS];
        int m_ledNumAction[NUM_ACTION] = {8,9,10,11,3,2,1,0};
        // patch 
        int m_patchSelected{-1};
        // relay (mic switcher) 
        int m_relayState{OPEN};
        // FX 
        bool m_fx[NUM_FX];
        // song 
        int m_currSong{0};
        bool m_nextSong{false};
        // transport 



    public:
        // constructor
        Stjorn();

        // Set functions
        void setState(int stNew);
        bool confirmState(int state);
        void setPressed(int btn, bool state);
        void setLed(int type, int led, bool state, int colour);
        void selectPatch(int patch);
        void setRelay(int state);
        void setFX(int fx, bool state);
        void sendTap();
        void saveSongVar();
        void setSong(int song);
        void setNext(int press, int song);

        // Get functions
        int state() {return m_stCurr;}
        int prevState() {return m_stPrev;}
        bool stateChange() {return m_stChange;}
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