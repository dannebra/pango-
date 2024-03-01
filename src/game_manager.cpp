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

    m_Tex = new AnimatedTexture("pango_title.png", AnimatedTexture::Attributes{0, 0, 210, 82, 0, 0.0f, AnimatedTexture::AnimationDirection::horizontal});
    m_Tex->SetPosition(Vector::Vector2{Graphics::screenWidth * 0.5f, Graphics::screenHeight * 0.3f});

    m_Text = new Texture("Start", "ModernDOS8x14.ttf", 22, SDL_Color{0xff, 0xff, 0xff});
    m_Text->SetPosition(Vector::Vector2{Graphics::screenWidth * 0.5f, Graphics::screenHeight * 0.5f});
    m_Text->SetParent(m_Tex);
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

    if (m_InputManager->KeyPressed(SDL_SCANCODE_RETURN)) {
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

    if (m_InputManager->KeyDown(SDL_SCANCODE_W)) {
        m_Tex->Translate(Vector::Multiply(Vector::Vector2(0.0f, -40.0f), m_Timer->DeltaTime()));
    } else if (m_InputManager->KeyDown(SDL_SCANCODE_S)) {
        m_Tex->Translate(Vector::Multiply(Vector::Vector2(0.0f, 40.0f), m_Timer->DeltaTime()));
    }

    LateUpdate();
}

void GameManager::Render()
{
    m_Tex->Update();
    m_Text->Update();

    m_Graphics->ClearBackBuffer();

    m_Tex->Render();
    m_Text->Render();

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