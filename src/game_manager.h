#ifndef _GAME_MANAGER_
#define _GAME_MANAGER_

#include "animated_texture.h"
#include "asset_manager.h"
#include "audio_manager.h"
#include "input_manager.h"

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

        SDL_Event m_Event{};
        AnimatedTexture *m_Tex;
        Texture *m_Text;
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