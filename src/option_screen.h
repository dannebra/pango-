#ifndef _OPTION_SCREEN_H
#define _OPTION_SCREEN_H

#include "animated_texture.h"
#include "input_manager.h"

class OptionScreen
{
    public:
        OptionScreen();
        ~OptionScreen();
        void Update();
        void Render();
    private:
        Texture *m_OptionText; // TODO: Temp
        InputManager *m_Input;

};

#endif