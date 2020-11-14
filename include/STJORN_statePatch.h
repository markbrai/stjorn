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

#ifndef STJORN_STATEPATCH_H
#define STJORN_STATEPATCH_H

#include <Arduino.h>
#include <Bounce2.h>
#include "STJORN_definitions.h"

void statePatch(Bounce *fs);

void procFsPatch(Bounce fs, int fsNum);

void procLedPatch();

void procDisplayPatch();



#endif
