#include <Bounce2.h>
#include "STJORN_definitions.h"

void updateFootswitches(Bounce *fs){

    for (int i=0; i < NUM_FS; i++){
        fs[i].update();
    }
}