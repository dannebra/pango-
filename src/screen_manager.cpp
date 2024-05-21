#include "screen_manager.h"

ScreenManager *ScreenManager::s_Instance = nullptr;

ScreenManager *ScreenManager::Instance()
{
    if (s_Instance == nullptr) {
        s_Instance = new ScreenManager();
    }

    return s_Instance;
}

void ScreenManager::FreeResources()
{
    delete s_Instance;
    s_Instance = nullptr;
}

ScreenManager::ScreenManager()
{
    m_StartScreen = new StartScreen();
    m_CurrentScreen = Screen::start;
    m_OptionScreen = new OptionScreen();
    m_PlayScreen = new PlayScreen();

    m_Input = InputManager::Instance();
}

ScreenManager::~ScreenManager()
{
    delete m_StartScreen;
    m_StartScreen = nullptr;
    delete m_PlayScreen;
    m_PlayScreen = nullptr;
    delete m_OptionScreen;
    m_OptionScreen = nullptr;

    m_Input = nullptr;
}

void ScreenManager::Update()
{
    switch (m_CurrentScreen)
    {
        case Screen::start:
            m_StartScreen->Update();
            if ((m_StartScreen->GetSelectedMode() == StartScreen::SelectedMode::options) &&
                (m_Input->KeyPressed(SDL_SCANCODE_RETURN))) {
                m_CurrentScreen = Screen::options;
            } else if (m_Input->KeyPressed(SDL_SCANCODE_RETURN)) {
                m_CurrentScreen = Screen::play;
            }
            break;
        case Screen::options:
            m_OptionScreen->Update();
            if (m_Input->KeyPressed(SDL_SCANCODE_BACKSPACE)) {
                m_CurrentScreen = Screen::start;
            }
            break;
        case Screen::play:
            m_PlayScreen->Update();
            if (m_Input->KeyPressed(SDL_SCANCODE_BACKSPACE)) {
                m_CurrentScreen = Screen::start; // temp for testing
            }
            break;
    }
}

void ScreenManager::Render()
{
    switch (m_CurrentScreen)
    {
        case Screen::start:     { m_StartScreen->Render();  break; }
        case Screen::options:   { m_OptionScreen->Render(); break; }
        case Screen::play:      { m_PlayScreen->Render();   break; }
    }
}

