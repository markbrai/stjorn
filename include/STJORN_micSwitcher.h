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

/* ------------ MIC SWITCHER --------------
*  Functions for controlling mic switcher relay
*  ---------------------------------------- */

#ifndef STJORN_MICSWITCHER_H
#define STJORN_MICSWITCHER_H

#include <Arduino.h>
#include "STJORN_definitions.h"
#include <Bounce2.h>

void processRelay(Bounce fs);

void triggerRelay(bool state);


#endif 