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

/* ------------ DISPLAY  --------------
*  Functions for setting display buffers
*  ---------------------------------------- */

#ifndef STJORN_DISPLAY_H
#define STJORN_DISPLAY_H

#include <Arduino.h>
#include "STJORN_definitions.h"
#include "STJORN_stateClass.h"

void setDisplayMain();
void setDisplayPatch();
void setDisplaySong();
void setDisplayCurr();
void setDisplayNext();



#endif 