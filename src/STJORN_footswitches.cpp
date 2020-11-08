#include <Bounce2.h>
#include "STJORN_definitions.h"

void updateFootswitches(Bounce *b){

    for (int i=0; i < NUM_FS; i++){
        b[i].update();
    }
}