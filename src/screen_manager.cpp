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

    m_Input = InputManager::Instance();
}

ScreenManager::~ScreenManager()
{
    delete m_StartScreen;
    m_StartScreen = nullptr;

    m_Input = nullptr;
}

void ScreenManager::Update()
{
    switch (m_CurrentScreen)
    {
        case Screen::start:
            m_StartScreen->Update();
            if (m_Input->KeyPressed(SDL_SCANCODE_DOWN)) { // TODO: Get this from start screen
                m_CurrentScreen = Screen::options;
            }
            break;
        case Screen::options:
            m_OptionScreen->Update();
            if (m_Input->KeyPressed(SDL_SCANCODE_RETURN)) {
                m_CurrentScreen = Screen::start;
            }
            break;
        case Screen::play:
            break;
            // TODO: implement play screen
    }
}

void ScreenManager::Render()
{
    switch (m_CurrentScreen)
    {
        case Screen::start:     { m_StartScreen->Render(); break; }
        case Screen::options:   { m_OptionScreen->Render(); break; }
        case Screen::play:      { break; } // TODO: implement play screen
    }
}

