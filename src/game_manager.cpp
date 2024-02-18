#include "game_manager.h"

GameManager *GameManager::s_Instance = nullptr;

GameManager::GameManager()
{
    m_Quit = false;
    m_AudioManager = AudioManager::Instance();
    if (!m_AudioManager->HasInitialized()) {
        m_Quit = true;
    }

    m_Graphics = Graphics::Instance();
    if (!m_Graphics->HasInitialized()) {
        m_Quit = true;
    }

    m_Timer = Timer::Instance();

    m_AssetManager = AssetManager::Instance();
    m_Tex = new AnimatedTexture("pango_title.png", AnimatedTexture::Attributes{0, 0, 210, 82, 0, 0.0f, AnimatedTexture::AnimationDirection::horizontal});
    m_Tex->SetPosition(Vector::Vector2{Graphics::screenWidth * 0.5f, Graphics::screenHeight * 0.4f});

    m_InputManager = InputManager::Instance();
}

GameManager::~GameManager()
{
    m_AudioManager->FreeResources();
    m_AudioManager = nullptr;

    m_Graphics->FreeResources();
    m_Graphics = nullptr;

    m_Timer->FreeResources();
    m_Timer = nullptr;

    m_AssetManager->Release();
    m_AssetManager = nullptr;

    m_InputManager->Release();
    m_AssetManager = nullptr;
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

void GameManager::Run()
{
    m_AudioManager->LoadMusic("../assets/audio/title_theme.mp3");
    m_AudioManager->PlayMusic();
    while (!m_Quit)
    {
        m_Timer->Update();
        while (SDL_PollEvent(&m_Event)) {
            if (m_Event.type == SDL_QUIT) {
                m_Quit = true;
            }
        }

        m_InputManager->Update();
        if (m_InputManager->KeyDown(SDL_SCANCODE_M)) {
            m_AudioManager->ToggleMusic();
        } else if (m_InputManager->KeyDown(SDL_SCANCODE_ESCAPE)) {
            m_Quit = true;
        }

        if (m_Timer->DeltaTime() >= (1.0f / frameRate)) {
            if (m_InputManager->KeyDown(SDL_SCANCODE_W)) {
                m_Tex->Translate(Vector::Multiply(Vector::Vector2(0.0f, -40.0f), m_Timer->DeltaTime()));
            } else if (m_InputManager->KeyDown(SDL_SCANCODE_S)) {
                m_Tex->Translate(Vector::Multiply(Vector::Vector2(0.0f, 40.0f), m_Timer->DeltaTime()));
            }

            m_Tex->Update();
            m_Graphics->Render();
            m_Timer->Reset();
            m_Tex->Render();
        }
    }
}