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

/* ------------ STATE - TRACKS --------------
*  Functions for controlling Ableton Live Tracks
*  ---------------------------------------- */

#ifndef STJORN_STATETRACKS_H
#define STJORN_STATETRACKS_H

#include <Arduino.h>
#include <Bounce2.h>
#include "STJORN_definitions.h"

void stateTracks(Bounce *fs);
void procFsTracks(Bounce fs, int fsNum);
void procExprTracks();
void procLedTracks();
void procDisplayTracks();

#endif