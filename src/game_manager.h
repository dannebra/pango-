#ifndef _GAME_MANAGER_
#define _GAME_MANAGER_

#include "audio_manager.h"
#include "graphics.h"

class GameManager
{
    private:
        static GameManager *s_Instance;
        bool m_Quit;
        Graphics *m_Graphics;
        AudioManager *m_AudioManager;

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