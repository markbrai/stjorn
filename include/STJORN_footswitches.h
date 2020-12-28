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

/* ------------ FOOTSWITCHES --------------
*  Functions for processing footswitches
*  ---------------------------------------- */

#ifndef STJORN_FOOTSWITCHES_H
#define STJORN_FOOTSWITCHES_H

#include <Bounce2.h>

void updateFootswitches(Bounce *fs);

int fsShortLong(Bounce fs, int fsNum);

bool fsTapEngage(Bounce fs, int fsNum);

void updateExpression(int prox);

void sendExpression();

#endif 

