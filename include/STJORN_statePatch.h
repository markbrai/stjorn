#ifndef STJORN_STATEPATCH_H
#define STJORN_STATEPATCH_H

#include <Arduino.h>
#include <Bounce2.h>
#include "STJORN_definitions.h"

void statePatch(Bounce *fs);

void procFsPatch(Bounce fs, int fsNum);


#endif
