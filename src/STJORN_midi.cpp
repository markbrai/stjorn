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
            processNote(channel,data1,data2);
            break;

        case usbMIDI.NoteOn:
            processNote(channel,data1,data2);
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

void processNote(byte channel, byte noteNum, byte velocity){

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
        case CC_AUXFX:     // aux FX num
            stjorn.setAuxFX(value);
            stjorn.setAux(false);
            break;
        default:
            break;
    }
} else if (channel == MIDI_CH_LIVE){
    switch (ccNum) {
        case CC_LOOPER_IN:
            if (value <= LOOPER_OVERDUB){
                stjorn.setLooper(value);
            }
            break;
        case CC_TRANSPORT:
            if (value == CC_VAL_STOP){
                stjorn.setTransport(TRAN_STOP);
            } else if (value == CC_VAL_PLAY){
                stjorn.setTransport(TRAN_PLAY);
            } else if (value == CC_VAL_CLICK){
                stjorn.setClickOnly(true);
            } else if (value == CC_VAL_SONG){
                stjorn.setClickOnly(false);
            }
            break;
        case CC_CYCLE:
            if (value == CC_VAL_NEXT){
                stjorn.setFollow(FLW_NEXT);
            } else if (value == CC_VAL_ONESHOT){
                stjorn.setFollow(FLW_ONESHOT);
                stjorn.setTransport(TRAN_CYCLE);
            } else if (value == CC_VAL_CYCLE){
                stjorn.setFollow(FLW_CYCLE);
                stjorn.setTransport(TRAN_CYCLE);
            }
            break;
        case CC_GOTO1 ... CC_GOTO4:
            stjorn.setFollow(ccNum-3);
            stjorn.setTransport(TRAN_GOTO);
            break;
        case CC_CYCLEOK:
            if (value == CC_VAL_CYCLE_OK){
                stjorn.setCycleAllowed(true);
            } else if (value == CC_VAL_CYCLE_NOK){
                stjorn.setCycleAllowed(false);
            }
            break;
        case CC_TRAXMUTE:
            if (value == CC_VAL_TRAX_MUTE){
                stjorn.setTraxMute(true);
            } else if (value == CC_VAL_TRAX_UNMUTE){
                stjorn.setTraxMute(false);
            }
            break;
        case CC_CUEMUTE:
            if (value == CC_VAL_CUE_MUTE){
                stjorn.setCueMute(true);
            } else if (value == CC_VAL_CUE_UNMUTE){
                stjorn.setCueMute(false);
            }
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


    if (pSysExArray[SYS_BYTE_ID] == SYSEX_STJORN && channel == MIDI_CH_LIVE){
        switch (pSysExArray[SYS_BYTE_TYPE]){
            case SYSEX_SCENES:
                for (int i = 0; i < length; i++){
                    stjorn.setScenes(i,pSysExArray[i]);
                }
                break;

            default:
                break;
        }

    }



}