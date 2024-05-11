#include "option_screen.h"

OptionScreen::OptionScreen()
{
    m_OptionText = new Texture("Options", "ModernDOS8x14.ttf", 22, SDL_Color{0xff, 0xff, 0xff});
    m_OptionText->SetPosition(Vector::Vector2(Graphics::Instance()->screenWidth * 0.5f, Graphics::Instance()->screenHeight * 0.5f));
    m_Input = InputManager::Instance();
}

OptionScreen::~OptionScreen()
{
    delete m_OptionText;
    m_OptionText = nullptr;

    m_Input = nullptr;
}

void OptionScreen::Update()
{
    // TODO: Implement options
}

void OptionScreen::Render()
{
    m_OptionText->Render();
}