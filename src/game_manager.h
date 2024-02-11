#ifndef _GAME_MANAGER_
#define _GAME_MANAGER_

#include "audio_manager.h"
#include "texture.h"
#include "timer.h"

class GameManager
{
    private:
        static GameManager *s_Instance;
        bool m_Quit;
        const int frameRate = 60;

        AudioManager *m_AudioManager;
        Graphics *m_Graphics;
        Timer *m_Timer;

        SDL_Event m_Event{};

    public:
        static GameManager *Instance();
        static void ShutdownGame();
        void Run();

    private:
        GameManager();
        ~GameManager();
};

#endif