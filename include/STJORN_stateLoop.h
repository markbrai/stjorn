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

#ifndef STJORN_STATELOOP_H
#define STJORN_STATELOOP_H

#include <Arduino.h>
#include <Bounce2.h>
#include "STJORN_definitions.h"

void stateLoop(Bounce *fs);
void procFsLoop(Bounce fs, int fsNum);
int procLoopControl(int fsNum, int press);
void procExprLoop();
void procLedLoop();
void procDisplayLoop();

#endif