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

    public:
        // constructor
        Stjorn();

        // Set functions
        void setState(int stNew);
        void setPressed(int btn, bool state);
        void setLed(int led, bool state, int colour);
        void selectPatch(int patch);

        // Get functions
        int state() {return m_stCurr;}
        int prevState() {return m_stPrev;}
        bool isPressed(int btn);
        bool isLit(int led);
        int isColour(int led);
        int patch() {return m_patchSelected;}
};


extern Stjorn stjorn;

#endif