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

/* ------------ DISPLAY  --------------
 *  Functions for setting display buffers
 *  ---------------------------------------- */

#include <Arduino.h>
#include "STJORN_definitions.h"
#include "STJORN_stateClass.h"
#include "STJORN_display.h"

void setDisplayMain()
{
    setDisplayPatch();
    setDisplaySong();
    setDisplayCurr();
    setDisplayNext();
}

void setDisplayPatch()
{

    char dispPatch[NUM_PATCH][DIGIT_RIG] = {{'A', 'M'},
                                            {'R', '2'},
                                            {'D', '2'},
                                            {'L', '2'},
                                            {'C', 'L'},
                                            {'R', '1'},
                                            {'D', '1'},
                                            {'L', '1'}};

    if (stjorn.patch() == -1)
    {
        stjorn.setDisplay(BLK_RIG, 0, '-');
        stjorn.setDisplay(BLK_RIG, 1, '-');
    }
    else
    {
        for (int i = 0; i < DIGIT_RIG; i++)
        {
            char ascii = dispPatch[stjorn.patch()][i];
            stjorn.setDisplay(BLK_RIG, i, ascii);
        }
    }
}

void setDisplaySong()
{

    for (int i = 0; i < DIGIT_SONG; i++)
    {
        stjorn.setDisplay(BLK_SONG, i, stjorn.songDigit(i));
    }
}

void setDisplayCurr()
{
    char ascii;

    for (int i = 0; i < DIGIT_CURR; i++)
    {
        if (stjorn.transport() == TRAN_STOP)
        {
            ascii = '-';
        }
        else
        {
            ascii = stjorn.scene(SCENE_CURR, i);
        }
        stjorn.setDisplay(BLK_CURR, i, ascii);
    }
}

void setDisplayNext()
{
    char ascii = '_';
    char loop[4] = {'L', 'O', 'O', 'P'};

    for (int i = 0; i < DIGIT_NEXT; i++)
    {
        switch (stjorn.transport())
        {
        case TRAN_PLAY:
            ascii = stjorn.scene(SCENE_NEXT, i);
            break;
        case TRAN_STOP:
            ascii = '-';
            break;
        case TRAN_CYCLE:
            ascii = loop[i];
            break;
        case TRAN_GOTO:
            switch (stjorn.follow())
            {
            case FLW_GOTO1:
                ascii = stjorn.scene(SCENE_G1, i);
                break;
            case FLW_GOTO2:
                ascii = stjorn.scene(SCENE_G2, i);
                break;
            case FLW_GOTO3:
                ascii = stjorn.scene(SCENE_G3, i);
                break;
            case FLW_GOTO4:
                ascii = stjorn.scene(SCENE_G4, i);
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
        stjorn.setDisplay(BLK_NEXT, i, ascii);
    }
}

const int coloursBright[10] = {RED,
                               BLUE,
                               GREEN,
                               YELLOW,
                               ORANGE,
                               WHITE,
                               PINK,
                               PURPLE,
                               CYAN,
                               DARK};

const int coloursDim[10] = {RED_DIM,
                            BLUE_DIM,
                            GREEN_DIM,
                            YELLOW_DIM,
                            ORANGE_DIM,
                            WHITE_DIM,
                            PINK_DIM,
                            PURPLE_DIM,
                            CYAN_DIM,
                            DARK};

int setLedColour(int colour_idx, bool state)
{

    int colour;
    if (state == true)
    {
        colour = coloursBright[colour_idx];
    }
    else
    {
        colour = coloursDim[colour_idx];
    }

    return colour;
}