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

/* ------------ TAP & CLICK --------------
*  Functions for controlling click and tap
*  ---------------------------------------- */

#ifndef STJORN_TAPCLICK_H
#define STJORN_TAPCLICK_H

#include <Arduino.h>
#include "STJORN_definitions.h"
#include <Bounce2.h>

void processTap(Bounce fs);

void processClick(Bounce fs);

#endif