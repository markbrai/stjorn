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

/* ------------ STATE - SONG --------------
*  Functions for selecting songs and controlling state
*  ---------------------------------------- */

#ifndef STJORN_STATESONG_H
#define STJORN_STATESONG_H

#include <Arduino.h>
#include <Bounce2.h>
#include "STJORN_definitions.h"

void stateSong(Bounce *fs);
void procFsSong(Bounce fs, int fsnum);
void procExprSong();
void procLedSong();
void procDisplaySong();




#endif