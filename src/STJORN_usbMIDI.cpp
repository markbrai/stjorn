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

// ************************* INPUT PROCESSING FUNCTIONS *********************************************
/* These functions take the incoming MIDI message and split it in to it's component parameters
 * Some basic parsing of 'non-STJORN' channels is made to exit processing if the message is
 * from a channel that does not contain useful information
 */
   void MidiInProcess(MidiType *midiType, int *midiChan, int *midiNum, int *midiVal) {

    *midiChan = MidiInGetChan();    // get MIDI channel
    if (*midiChan < MIDI_CH_OS){
            *midiChan = -1;
            return;                  // if channel is not from Live, GP, or OnSong then exit
       }  

    *midiType = MidiInGetType();    // get type of message

    *midiNum = MidiInGetNum();      // get message number (data1)

    *midiVal = MidiInGetVal();      // get message value (data2)


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

// ********************************** PARAMETER PARSING FUNCTIONS ********************
// These functions further process the incoming MIDI messages based on it's type


byte MidiProcessProgCh(int midiChan, int midiNum){
// parse the channel number and return the message number (data1) as a new song number
    byte newSongNum;

    if (midiChan == MIDI_CH_OS){
        newSongNum = -1;            // currently we don't do anything with prog changes received on OnSong channel
    } else {
        if (midiNum <= MAX_SONGS) { // check if message number is > max allowed songs
            newSongNum = (byte) midiNum;
        } else {
            newSongNum = -1;        // if message num is > max allowed return no new song
        }
    }

    return newSongNum;
}

ParamTgt MidiProcessTgt(int midiChan, int midiNum){
/* parse an incoming message to determine it's target
 * midiChan: What mode is the target parameter for
 */

ParamTgt paramTgt = TGT_NONE;

    switch (midiChan){
        case MIDI_CH_LIVE:        // determine which mode the message belongs to
            if ((midiNum > LIVE_NONE && midiNum <= LIVE_TRAXVOL) || (midiNum >= LIVE_VERSE && midiNum <= LIVE_CYCLEOK)){
                paramTgt = TGT_SONG;
            } else if (midiNum == LIVE_LOOPVOL){
                paramTgt = TGT_LOOP;
            } else if (midiNum == LIVE_PADVOL){
                paramTgt = TGT_PADS;
            } else {
                paramTgt = TGT_NONE;
            }
            break;

        case MIDI_CH_OS:          // we don't currently do anything with messages from OnSong

            paramTgt = TGT_NONE;
            break;
        
        case MIDI_CH_GP:

            paramTgt = TGT_RIG;     // send all messages from GP to Rig functions
            break;

        default:
            break;
    }

    return paramTgt;

}



void MidiProcessGPNote(int midiNum, int midiVal) {

}

void MidiProcessCC(){

}