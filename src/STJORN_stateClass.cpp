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
