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

/* ------------ STATE - MENU --------------
 *  Functions for controlling menu state
 *  ---------------------------------------- */

#ifndef STJORN_STATEMENU_H
#define STJORN_STATEMENU_H

#include <Bounce2.h>

void stateMenu(Bounce *fs);

void procDisplayMenu();

#endif
