#include "game_manager.h"

GameManager *GameManager::s_Instance = nullptr;

GameManager::GameManager()
{
    m_Quit = false;
    m_AudioManager = AudioManager::Instance();
    
    m_Graphics = Graphics::Instance();
    if (!m_Graphics->HasInitialized()) {
        m_Quit = true;
    }

    m_Timer = Timer::Instance();

    m_InputManager = InputManager::Instance();

    m_AssetManager = AssetManager::Instance();

    m_ScreenManager = ScreenManager::Instance();
}

GameManager::~GameManager()
{
    m_AudioManager->FreeResources();
    m_AudioManager = nullptr;

    m_AssetManager->FreeResources();
    m_AssetManager = nullptr;

    m_Graphics->FreeResources();
    m_Graphics = nullptr;

    m_Timer->FreeResources();
    m_Timer = nullptr;

    m_InputManager->FreeResources();
    m_AssetManager = nullptr;

    m_ScreenManager->FreeResources();
    m_ScreenManager = nullptr;
}

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

void GameManager::EarlyUpdate()
{
    m_InputManager->Update();
}

void GameManager::LateUpdate()
{
    m_InputManager->UpdatePreviousInput();
    m_Timer->Reset();
}

void GameManager::Update()
{
    EarlyUpdate();

    // TODO: Temp stuff, remove this
    if (m_InputManager->KeyDown(SDL_SCANCODE_ESCAPE)) {
        m_Quit = true;
    }

    if (m_InputManager->KeyDown(SDL_SCANCODE_M)) {
        m_AudioManager->PauseMusic();
    }

    if (m_InputManager->KeyDown(SDL_SCANCODE_N)) {
        m_AudioManager->ResumeMusic();
    }

    if (m_InputManager->KeyPressed(SDL_SCANCODE_F10)) {
        m_AudioManager->PlayMusic("game_start.mp3", 0);
    }

    if (m_InputManager->KeyReleased(SDL_SCANCODE_RETURN)) {
        m_AudioManager->PlaySfx("kick.mp3");
    }

    if (m_InputManager->MouseButtonPressed(InputManager::MouseButton::left)) {
        printf("Mouse button pressed\n");
    }

    if (m_InputManager->MouseButtonReleased(InputManager::MouseButton::left)) {
        printf("Mouse button released\n");
    }
    m_ScreenManager->Update();

    LateUpdate();
}

void GameManager::Render()
{
    m_Graphics->ClearBackBuffer();
    m_ScreenManager->Render();
    m_Graphics->Render();
}

void GameManager::Run()
{
    m_AudioManager->PlayMusic("title_theme.mp3");
    while (!m_Quit)
    {
        m_Timer->Update();
        while (SDL_PollEvent(&m_Event)) {
            if (m_Event.type == SDL_QUIT) {
                m_Quit = true;
            }
        }

        if (m_Timer->DeltaTime() >= (1.0f / frameRate)) {
            Update();
            Render();
        }
    }
}