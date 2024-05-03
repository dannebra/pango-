#include "start_screen.h"

void StartScreen::Update()
{
    if (m_Input->KeyPressed(SDL_SCANCODE_DOWN) || m_Input->KeyPressed(SDL_SCANCODE_UP)) {
        ChangeSelectedMode();
    }
}

void StartScreen::Render()
{
    m_CurrentScoreText->Render();
    m_TopScoreText->Render();
    m_TopScore->Render();
    m_Score->Render();
    m_Logo->Render();
    m_StartGameText->Render();
    m_OptionsText->Render();

    m_Cursor->Render();
}

StartScreen::StartScreen()
{
    m_TopBar = new GameEntity(Vector::Vector2(Graphics::Instance()->screenWidth * 0.5f, 20.0f));
    m_TopBar->SetParent(this);

    m_TopScoreText = new Texture("High Score", "ModernDOS8x14.ttf", 22, SDL_Color{0xff, 0xff, 0xff});
    m_TopScoreText->SetParent(m_TopBar);
    m_TopScoreText->SetPosition(Vector::Vector2(-Graphics::Instance()->screenWidth * 0.20f, 0));

    m_CurrentScoreText = new Texture("Score", "ModernDOS8x14.ttf", 22, SDL_Color{0xff, 0xff, 0xff});
    m_CurrentScoreText->SetParent(m_TopBar);
    m_CurrentScoreText->SetPosition(Vector::Vector2(-Graphics::Instance()->screenWidth * 0.45f, 0));

    m_TopScore = new ScoreBoard();
    m_TopScore->SetParent(m_TopBar);
    m_TopScore->SetPosition(Vector::Vector2(-Graphics::Instance()->screenWidth * 0.12f, 25));
    m_TopScore->SetScore(124214124);

    m_Score = new ScoreBoard();
    m_Score->SetParent(m_TopBar);
    m_Score->SetPosition(Vector::Vector2(-Graphics::Instance()->screenWidth * 0.415f, 25));

    m_Logo = new AnimatedTexture("pango_title.png", AnimatedTexture::Attributes{0, 0, 210, 82, 0, 0.0f, AnimatedTexture::AnimationDirection::horizontal});
    m_Logo->SetPosition(Vector::Vector2{Graphics::screenWidth * 0.5f, Graphics::screenHeight * 0.3f});

    m_Selections = new GameEntity(Vector::Vector2{Graphics::screenWidth * 0.5f, Graphics::screenHeight * 0.5f});
    m_Selections->SetParent(this);

    m_StartGameText = new Texture("Start", "ModernDOS8x14.ttf", 22, SDL_Color{0xff, 0xff, 0xff});
    m_StartGameText->SetParent(m_Selections);
    m_StartGameText->SetPosition(Vector::Vector2{-20.0f, 0.0f});

    m_OptionsText = new Texture("Options", "ModernDOS8x14.ttf", 22, SDL_Color{0xff, 0xff, 0xff});
    m_OptionsText->SetParent(m_Selections);
    m_OptionsText->SetPosition(Vector::Vector2{-8.0f, 30.0f});

    m_Cursor = new Texture("cursor.png");
    m_Cursor->SetParent(m_Selections);
    m_Cursor->SetPosition(Vector::Vector2{-80.0f, 0.0f});
    m_CursorStartPosition = m_Cursor->GetPosition(Space::local);
    m_CursorOffset = Vector::Vector2{0.0f, 30.0f};
   
    m_SelectedMode = SelectedMode::start;

    m_Input = InputManager::Instance();
}

void StartScreen::ChangeSelectedMode()
{
    if (m_SelectedMode == SelectedMode::start) {
        m_SelectedMode = SelectedMode::options;
        m_Cursor->SetPosition(Vector::Add(m_CursorStartPosition, m_CursorOffset));
    } else if (m_SelectedMode == SelectedMode::options) {
        m_SelectedMode = SelectedMode::start;
        m_Cursor->SetPosition(m_CursorStartPosition);
    }
}

StartScreen::~StartScreen() 
{
    delete m_TopBar;
    m_TopBar = nullptr;
    delete m_TopScoreText;
    m_TopScoreText = nullptr;
    delete m_CurrentScoreText;
    m_CurrentScoreText = nullptr;
    delete m_TopScore;
    m_TopScore = nullptr;
    delete m_Score;
    m_Score = nullptr;

    delete m_Logo;
    m_Logo = nullptr;

    delete m_Selections;
    m_Selections = nullptr;

    delete m_StartGameText;
    m_StartGameText = nullptr;

    delete m_OptionsText;
    m_OptionsText = nullptr;

    delete m_Cursor;
    m_Cursor = nullptr;
}