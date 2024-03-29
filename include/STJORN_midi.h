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

/* ------------ STATE MIDI --------------
*  MIDI functions to read and process
*  ---------------------------------------- */

#ifndef STJORN_MIDI_H
#define STJORN_MIDI_H

#include <Arduino.h>
#include "STJORN_definitions.h"
#include "STJORN_stateClass.h"

void processMidi();
void processNote(byte channel, byte noteNum, byte velocity);
void processControlChange(byte channel, byte ccNum, byte value);
void processProgramChange(byte channel, byte progNum);
bool processFXMidi(byte noteNum, byte velocity);
void processSysEx(byte channel, const byte pSysExArray[], int length);

#endif