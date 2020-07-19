/* ------------ STJORN controller --------------
 *  Code written for Teensy 3.2 micro-controller
 *  Teensy USB Type should be set to 'MIDI' 
 * 
 * https://github.com/markbrai/stjorn 
 * https://hackaday.io/project/162616-stjrn
 * 
 * https://www.gigperformer.com
 * 
 */

/* ------------ PRESETUP --------------
 * USB MIDI functions for processing incoming
 * MIDI and setting up messages to send out
   ------------------------------------ */

#ifndef STJORN_USBMIDI_H
#define STJORN_USBMIDI_H

#include "STJORN_definitions.h"
#include <Arduino.h>

// ************************* INPUT PROCESSING FUNCTIONS *********************************************

void MidiInProcess(MidiType *midiType, int *midiChan, int *midiNum, int *midiVal);

MidiType MidiInGetType();   // Parse type of incoming MIDI message

int MidiInGetChan();        // Parse the channel of the incoming MIDI message

int MidiInGetNum();         // Parse the parameter number of the incoming MIDI message

int MidiInGetVal();         // Pase the parameter value of the incoming MIDI message

// ********************************** PARAMETER PARSING FUNCTIONS ********************

byte MidiProcessProgCh(int midiChan, int midiNum);    // Process program change and output new song number

ParamTgt MidiProcessTgt(int midiChan, int midiNum);            // determine target of message

#endif