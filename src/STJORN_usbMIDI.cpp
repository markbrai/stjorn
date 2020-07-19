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

   #include <Arduino.h>
   #include "STJORN_definitions.h"
   #include "STJORN_usbMIDI.h"

   void MidiInProcess(MidiType *midiType, int *midiChan, int *midiNum, int *midiVal) {
       
       *midiType = MidiInGetType();
       *midiChan = MidiInGetChan();


   }

   MidiType MidiInGetType(){
       byte type;
       MidiType midiTypeTemp;

       type = usbMIDI.getType();

       switch(type) {
            case usbMIDI.NoteOff:   // 0x80
                midiTypeTemp = MIDI_NOTEOFF;
                break;
            case usbMIDI.NoteOn:    // 0x90
                midiTypeTemp = MIDI_NOTEON;
                break;
            case usbMIDI.ControlChange: // 0xB0
                midiTypeTemp = MIDI_CC;
                break;
            case usbMIDI.ProgramChange:  // 0xC0
                midiTypeTemp = MIDI_PROG;
                break;
            default:
                midiTypeTemp = MIDI_NONE;
       }

        return midiTypeTemp;

   }

   int MidiInGetChan(){

   }

   int MidiInGetNum(){

   }

   int MidiInGetVal(){
       
   }