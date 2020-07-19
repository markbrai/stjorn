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

    *midiChan = MidiInGetChan();
    if (*midiChan < MIDI_CH_OS){
           return;                  // if channel is not from Live, GP, or OnSong then exit
       }  

    *midiType = MidiInGetType();
    if (*midiType == MIDI_PROG){
        return;
    }

    *midiNum = MidiInGetNum();

    *midiVal = MidiInGetVal();




   }

   MidiType MidiInGetType(){
       int type;
       MidiType midiTypeTemp;

       type = (int) usbMIDI.getType();

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
       int midiChanTmp;

       midiChanTmp =  (int) usbMIDI.getChannel();

       if (midiChanTmp < MIDI_CH_OS || midiChanTmp > MIDI_CH_LIVE){
           midiChanTmp = -1;
       } 

       return midiChanTmp;

   }

   int MidiInGetNum(){
       int midiNumTmp;

       midiNumTmp = (int) usbMIDI.getData1();

       return midiNumTmp;

   }

   int MidiInGetVal(){
       int midiValTmp;

       midiValTmp = (int) usbMIDI.getData2();

       return midiValTmp;

   }