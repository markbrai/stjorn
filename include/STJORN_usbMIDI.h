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

void MidiInProcess(MidiType *midiType, int *midiChan, int *midiNum, int *midiVal);

 MidiType MidiInGetType();
 int MidiInGetChan();
 int MidiInGetNum();
 int MidiInGetVal();




#endif