#ifndef _GAME_LOOP_H_
#define _GAME_LOOP_H_

#include "input.h"
#include <SDL2/SDL.h>

namespace pango
{
    bool PangoLoop(keyboard_inputs &inputs);
}

#endif