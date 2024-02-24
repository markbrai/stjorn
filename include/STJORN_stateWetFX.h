/* ------------ STJORN controller --------------
 *  Code written for Teensy 3.2 micro-controller
 *  Teensy USB Type should be set to 'MIDI'
 *
 * https://github.com/markbrai/stjorn
 * https://hackaday.io/project/162616-stjrn
 *
 * https://www.gigperformer.com
 *
 * Mark Braithwaite, 2024
 *
 */

/* ------------ STATE - FX --------------
 *  Functions for selecting  Wet FX and controlling state
 *  ---------------------------------------- */

#ifndef STJORN_STATEWETFX_H
#define STJORN_STATEWETFX_H

#include <Arduino.h>
#include <Bounce2.h>
#include "STJORN_definitions.h"

void stateWetFx(Bounce *fs);

void procFsWetFx(Bounce fs, int fsnum);

void procWetFxMod(int fsNum);

void procWetFxDly(int fsNum);

void procWetFxVrb(int fsNum);

void procLedWetFx();

void procDisplayWetFx();

void procExprWetFx();

#endif