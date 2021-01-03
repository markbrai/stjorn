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
    byte type = usbMIDI.getType();;
    byte channel = usbMIDI.getChannel();
    byte data1 = usbMIDI.getData1();
    byte data2 = usbMIDI.getData2();

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

        case usbMIDI.SystemExclusive:
            const byte *pSysExArray = usbMIDI.getSysExArray();
            int pSysExArrayLength = usbMIDI.getSysExArrayLength();
            
            processSysEx(channel, pSysExArray, pSysExArrayLength);

            
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
} else if (channel == MIDI_CH_LIVE){
    switch (ccNum) {
        case 50:
            if (value <= LOOPER_OVERDUB){
                stjorn.setLooper(value);
            }
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

void processSysEx(byte channel, const byte pSysExArray[], int length){
#define SYS_BYTE_ID 1
#define SYS_BYTE_TYPE 2
#define SYS_BYTE_CURR 3
#define SYS_BYTE_G1 7
#define SYS_BYTE_G2 11
#define SYS_BYTE_G3 15
#define SYS_BYTE_G4 19
#define SYS_BYTE_NEXT 23
#define SYSEX_STJORN 102
#define SYSEX_SCENES 83

    if (pSysExArray[SYS_BYTE_ID] == SYSEX_STJORN && channel == MIDI_CH_LIVE){
        switch (pSysExArray[SYS_BYTE_TYPE]){
            case SYSEX_SCENES:
                for (int i = SYS_BYTE_CURR; i < length; i++){
                    stjorn.setScenes(i,pSysExArray[i]);
                }

                break;

            default:
                break;
        }

    }



}