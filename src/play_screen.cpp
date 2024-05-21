#include "play_screen.h"

PlayScreen::PlayScreen()
{
    m_Timer = Timer::Instance();
    m_InputManager = InputManager::Instance();
    m_PlaySidebar = new PlaySidebar();
    m_PlaySidebar->SetParent(this);
    m_PlaySidebar->SetPosition(Vector::Vector2{70.0f, 20.0f});
    m_PlaySidebar->SetHighScore(100);
}

PlayScreen::~PlayScreen()
{
    m_Timer = nullptr;
    m_InputManager = nullptr;

    delete m_PlaySidebar;
    m_PlaySidebar = nullptr;
}

void PlayScreen::Update()
{
    m_PlaySidebar->Update();
}

void PlayScreen::Render()
{
    m_PlaySidebar->Render();
}