#ifndef _SCREEN_MANAGER_H_
#define _SCREEN_MANAGER_H_

#include "option_screen.h"
#include "start_screen.h"

class ScreenManager
{
    public:
        static ScreenManager *Instance();
        static void FreeResources();
        void Update();
        void Render();

    private:
        enum class Screen {
            start,
            options,
            play,
        };

        static ScreenManager *s_Instance;
        InputManager *m_Input;
        StartScreen *m_StartScreen;
        OptionScreen *m_OptionScreen;

        Screen m_CurrentScreen{Screen::start};

    private:
        ScreenManager();
        ~ScreenManager();

};

#endif