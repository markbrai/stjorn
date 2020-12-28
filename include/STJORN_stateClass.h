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
        int m_stLedCol[NUM_STATES] = {WHITE,BLUE,PURPLE,RED,WHITE,BLUE};
        int getStateLed(int state);
        // footswitch 
        bool m_pressed[NUM_FS];
        // expression
        int m_exprProx{0};
        int m_exprProxPrev{0};
        bool m_exprChanged{false};
        // display
        char m_dispSong[2];
        char m_dispCurr[4];
        char m_dispNext[4];
        char m_dispRig[2];
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
        int m_fxAux{0};
        bool m_aux{false};
        bool m_auxPressed{false};
        bool m_tap{false};
        // song 
        int m_currSong{0};
        bool m_nextSong{false};
        void setSongDigits(int song);
        char m_songDigits[DIGIT_SONG] = {'0','1'};
        void sendSong(int press, int song);
        bool m_songPage{false};
        // transport 

        // looper
        int m_looperState{0};



    public:
        // constructor
        Stjorn();

        // Set functions
        void setState(int stNew);
        void confirmState(int state);
        void setPressed(int btn, bool state);
        void setLed(int type, int led, bool state, int colour);
        void selectPatch(int patch);
        void setRelay(int state);
        void setFX(int fx, bool state);
        void setAux();
        void setAux(bool state);
        void setAuxFX(int aux);
        void sendTap(bool state);
        void saveSongVar();
        void setSong(int song);
        void setSong(int press, int song);
        void setNext(int press, int song);
        void setDisplay(int block, int digit, char ascii );
        void setProx(int prox);
        void setSongPage(bool page);    // true sets page 2
        void setTap(bool state);
        void setLooper(int state);

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
        int aux() {return m_aux;}
        int auxFX() {return m_fxAux;}
        bool next() {return m_nextSong;}
        char ascii(int blk, int digit);
        int expression() {return m_exprProx;};
        int exprChanged() {return m_exprChanged;}
        int song() {return m_currSong;}
        char songDigit(int digit);    
        bool songPage() {return m_songPage;} 
        bool tap() {return m_tap;}
        int looper() {return m_looperState;}
};


extern Stjorn stjorn;

#endif