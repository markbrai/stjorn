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

/* ------------ STATE - FX --------------
*  Functions for selecting FX and controlling state
*  ---------------------------------------- */

#ifndef STJORN_STATEFX_H
#define STJORN_STATEFX_H

#include <Arduino.h>
#include <Bounce2.h>
#include "STJORN_definitions.h"

void stateFX(Bounce *fs);

void procFsFX(Bounce fs, int fsNum);

void procLedFX();

void procDisplayFX();

void procExprFX();


#endif
