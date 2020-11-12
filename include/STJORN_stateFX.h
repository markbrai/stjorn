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

/* ------------ STATE - PATCH --------------
*  Functions for selecting patches and controlling state
*  ---------------------------------------- */

#ifndef STJORN_STATEFX_H
#define STJORN_STATEFX_H

#include <Arduino.h>
#include <Bounce2.h>
#include "STJORN_definitions.h"

void stateFX(Bounce *fs);

void procFsFX(Bounce fs, int fsNum);


#endif
