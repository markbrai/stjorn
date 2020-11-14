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

void processMidi(){
    byte type;
    byte channel;
    byte data1;
    byte data2;

    type = usbMIDI.getType();
    channel = usbMIDI.getChannel();
    data1 = usbMIDI.getData1();
    data2 = usbMIDI.getData2();

    Serial.print("Ch:");
    Serial.print(channel,DEC);
    Serial.print(", note:");
    Serial.println(data1,DEC);

    int ledNum = -1;

    switch (type) {
        case usbMIDI.NoteOff:
            if (channel == MIDI_CH_GP){
                switch (data1) {
                    case 17:
                        ledNum = 8;
                        break;
                    case 18:
                        break;
                    case 19:
                        break;
                    case 21:
                        break;
                    case 22:
                        break;
                    case 23:
                        break;
                    default:
                        break;
                }

            if (ledNum >= 0){
                int colour;
                bool state;
                if (data2 > 64){
                    colour = BLUE;
                    state = true;
                } else {
                    colour = DARK;
                    state = false;
                }
                stjorn.setLed(ledNum,state,colour);
            }

            }
            break;
        
        default:
            break;
    }




}