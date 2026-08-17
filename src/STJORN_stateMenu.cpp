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

#include "STJORN_stateMenu.h"
#include "STJORN_definitions.h"
#include "STJORN_display.h"
#include "STJORN_footswitches.h"
#include "STJORN_stateClass.h"
#include <Bounce2.h>

void stateMenu(Bounce *fs) {
  // Process footswitch inputs
  for (int i = 0; i < NUM_FS; i++) {
    // For now, any state change button will exit menu
    // We can replicate the standard navigation
    if (i >= FS_ST_MN && i <= FS_ST_MX) {
      // Check if button pressed
      if (fs[i].fell()) {
        switch (i) {
        case FS_ST_SONG:
          stjorn.setState(ST_TRACKS); // Or ST_SONG? standard seems to be Tracks
                                      // or Song depending on context
          break;
        case FS_ST_RIG:
          stjorn.setState(ST_PATCH); // Standard behavior
          break;
        case FS_ST_LOOP:
          stjorn.setState(ST_LOOP);
          break;
          // FS_ST_NEXT is usually next song
        }
      }
    }
  }

  procDisplayMenu();

  // reset 'changed' state flag if just changed to this state
  stjorn.confirmState(ST_MENU);
}

void procDisplayMenu() {
  // Set "MENU" on Display 1
  stjorn.setDisplay(BLK_SONG, 0, 'M');
  stjorn.setDisplay(BLK_SONG, 1, 'E');
  stjorn.setDisplay(BLK_CURR, 0, 'N');
  stjorn.setDisplay(BLK_CURR, 1, 'U');

  // Set "ITEM" on Display 2 (partially) or just Item # on Display 3
  // Let's put Item # on Display 3
  stjorn.setDisplay(BLK_CURR, 2, ' ');
  stjorn.setDisplay(BLK_CURR, 3, ' ');

  stjorn.setDisplay(BLK_NEXT, 0, 'I');
  stjorn.setDisplay(BLK_NEXT, 1, 'T');
  stjorn.setDisplay(BLK_NEXT, 2, 'M');
  stjorn.setDisplay(BLK_NEXT, 3, ' ');

  int item = stjorn.menuItem();
  int tens = item / 10;
  int ones = item % 10;

  stjorn.setDisplay(BLK_RIG, 0, (tens > 0) ? (tens + '0') : ' ');
  stjorn.setDisplay(BLK_RIG, 1, ones + '0');
}
