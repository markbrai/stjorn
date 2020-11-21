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

#include <Arduino.h>
#include "STJORN_definitions.h"
#include "STJORN_stateClass.h"
#include "STJORN_midi.h"

void processMidi(){
    byte type;
    byte channel;
    byte data1;
    byte data2;

    type = usbMIDI.getType();
    channel = usbMIDI.getChannel();
    data1 = usbMIDI.getData1();
    data2 = usbMIDI.getData2();

    switch (type) {
        case usbMIDI.NoteOff:
            processNoteOff(channel,data1,data2);
            break;

        case usbMIDI.ControlChange:
            processControlChange(channel,data1,data2);
            break;

        case usbMIDI.ProgramChange:
            processProgramChange(channel,data1);
            break;
            
        default:
            break;

        
    }

}

void processNoteOff(byte channel, byte noteNum, byte velocity){

if (channel == MIDI_CH_GP){
    switch (noteNum) {

        case 1 ... 8:       // Patches
            stjorn.selectPatch(noteNum - 1);
            stjorn.setAux(false);   // on patch change, set Aux to false
            break;

        case 17 ... 24:     // FX
            if (noteNum == 20){       // ignore tap tempo
                break;
            } else if (noteNum == stjorn.auxFX() ){
                stjorn.setAux();
            }
            int fxNum = noteNum - 17;     // rebase FX number to 0
            bool fxState = processFXMidi(noteNum,velocity);
            stjorn.setFX(fxNum,fxState);
            break;

        default:
            break;
    }

}

}



void processControlChange(byte channel, byte ccNum, byte value){

if (channel == MIDI_CH_GP){
    switch (ccNum) {
        case 3:     // aux FX num
            stjorn.setAuxFX(value);
            stjorn.setAux(false);
            break;
        default:
            break;
    }
}

}

void processProgramChange(byte channel, byte progNum){

    switch (channel){
        case MIDI_CH_GP:
            stjorn.setSong(progNum);
            break;
        default:    
            break;
    }


}

bool processFXMidi(byte noteNum, byte velocity){

    bool fxState;

        if (velocity > 64){
            fxState = true;
        } else {
            fxState = false;
        }

        return fxState;
}