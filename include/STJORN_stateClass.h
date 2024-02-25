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
    int m_stLedCol[NUM_STATES] = {WHITE, BLUE, PURPLE, RED, PINK, BLUE, YELLOW};
    int getStateLed(int state);
    // footswitch
    bool m_pressed[NUM_FS];
    // expression
    int m_exprProx{0};
    int m_exprProxPrev{0};
    bool m_exprChanged{false};
    int m_exprType{EXPR_GTR_CC};
    // display
    char m_dispSong[2];
    char m_dispCurr[4];
    char m_dispNext[4];
    char m_dispRig[2];
    // leds
    bool m_ledState[NUM_LEDS];
    int m_ledColour[NUM_LEDS];
    int m_ledNumAction[NUM_ACTION] = {8, 9, 10, 11, 3, 2, 1, 0};
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
    int m_wet_fx_page{};
    bool m_wet_fx_active[3];
    bool m_fx_mod[4];
    bool m_fx_dly[4];
    bool m_fx_vrb[4];
    // song
    int m_currSong{0};
    bool m_nextSong{false};
    void setSongDigits(int song);
    char m_songDigits[DIGIT_SONG] = {'0', '1'};
    void sendSong(int press, int song);
    bool m_songPage{false};
    // transport
    int m_transport{0}; // stop, play, cycle
    bool m_clickOnly{0};
    int m_follow{0}; // next, one-shot, cycle, goto
    bool m_cycleAllowed{0};
    bool m_traxMute{0};
    bool m_cueMute{0};

    // scenes
    char m_sceneCurr[4] = {'-', '-', '-', '-'};
    char m_sceneNext[4] = {'-', '-', '-', '-'};
    char m_sceneGoto1[4] = {'-', '-', '-', '-'};
    char m_sceneGoto2[4] = {'-', '-', '-', '-'};
    char m_sceneGoto3[4] = {'-', '-', '-', '-'};
    char m_sceneGoto4[4] = {'-', '-', '-', '-'};

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
    void setFXMod(int fx, bool state);
    void setFXDly(int fx, bool state);
    void setFXVrb(int fx, bool state);
    void setFXWetOff(int type);
    void setFXWetPage(int type);
    void setFXWetActive(int fxNum, bool state);
    void setAux();
    void setAux(bool state);
    void setAuxFX(int aux);
    void sendTap(bool state);
    void saveSongVar();
    void setSong(int song);
    void setSong(int press, int song);
    void setNext(int press, int song);
    void setDisplay(int block, int digit, char ascii);
    void setProx(int prox);
    void setSongPage(bool page); // true sets page 2
    void setTap(bool state);
    void setLooper(int state);
    void setExprType(int type);
    void setScenes(int byteNum, byte charVal);
    void setTransport(int state);
    void setFollow(int state);
    void setClickOnly(bool state);
    void setCycleAllowed(bool state);
    void setTraxMute(bool state);
    void setCueMute(bool state);

    // Get functions
    int state() { return m_stCurr; }
    int prevState() { return m_stPrev; }
    bool stateChange() { return m_stChange; }
    bool isPressed(int btn);
    bool isLit(int led);
    int isColour(int led);
    int patch() { return m_patchSelected; }
    int relay() { return m_relayState; }
    bool fx(int fx);
    bool fx_mod(int fx);
    bool fx_dly(int fx);
    bool fx_vrb(int fx);
    int wet_fx_page() { return m_wet_fx_page; }
    bool wet_fx_active(int fx);
    int aux() { return m_aux; }
    int auxFX() { return m_fxAux; }
    bool next() { return m_nextSong; }
    char ascii(int blk, int digit);
    int expression() { return m_exprProx; };
    int exprChanged() { return m_exprChanged; }
    int song() { return m_currSong; }
    char songDigit(int digit);
    bool songPage() { return m_songPage; }
    bool tap() { return m_tap; }
    int looper() { return m_looperState; }
    int exprType() { return m_exprType; }
    char scene(int scene, int digit);
    int transport() { return m_transport; }
    int follow() { return m_follow; }
};

extern Stjorn stjorn;

#endif