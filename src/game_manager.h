#ifndef _GAME_MANAGER_
#define _GAME_MANAGER_

#include "asset_manager.h"
#include "audio_manager.h"
#include "start_screen.h"

class GameManager
{
    private:
        static GameManager *s_Instance;
        bool m_Quit;
        const int frameRate = 60;

        AudioManager *m_AudioManager;
        AssetManager *m_AssetManager;
        Graphics *m_Graphics;
        InputManager *m_InputManager;
        Timer *m_Timer;

        StartScreen *m_StartScreen;

        SDL_Event m_Event{};
    public:
        static GameManager *Instance();
        static void ShutdownGame();
        void Run();

    private:
        GameManager();
        ~GameManager();

        void EarlyUpdate();
        void Update();
        void LateUpdate();
        void Render();
};

#endif