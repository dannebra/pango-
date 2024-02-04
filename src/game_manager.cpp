#include "game_manager.h"

GameManager *GameManager::s_Instance = nullptr;

GameManager *GameManager::Instance()
{
    if (s_Instance == nullptr) {
        s_Instance = new GameManager();
    }

    return s_Instance;
}

void GameManager::ShutdownGame()
{
    delete s_Instance;
    s_Instance = nullptr;
}

void GameManager::Run()
{
    m_AudioManager->LoadMusic("../assets/audio/title_theme.mp3");
    m_AudioManager->PlayMusic();
    while (!m_Quit)
    {
        while (SDL_PollEvent(&m_Event)) {
            switch (m_Event.type) {
                case SDL_QUIT:
                {
                    std::exit(EXIT_SUCCESS); // TODO: Cleanup before exiting
                }
                case SDL_KEYDOWN:
                {
                    SDL_Keycode pressedKey = m_Event.key.keysym.sym;
                    if (pressedKey == SDLK_ESCAPE) {
                        std::exit(EXIT_SUCCESS); // TODO: Cleanup before exiting
                    } else if (pressedKey == SDLK_m) {
                        m_AudioManager->ToggleMusic();
                    }

                    break;
                }
            }
        }
    }
}

GameManager::GameManager()
{
    m_Quit = false;
    m_AudioManager = AudioManager::Instance();
    m_Graphics = Graphics::Instance();

    if (!m_Graphics->HasInitialized()) {
        m_Quit = true;
    }
}

GameManager::~GameManager()
{
    m_AudioManager->FreeResources();
    m_AudioManager = nullptr;

    m_Graphics->FreeResources();
    m_Graphics = nullptr;
}