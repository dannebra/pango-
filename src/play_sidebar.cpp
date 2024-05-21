#include "play_sidebar.h"

PlaySidebar::PlaySidebar()
{
    m_Timer = Timer::Instance();
    m_Audio = AudioManager::Instance();
    m_Background = new Texture("temp_background.png");
    m_Background->SetParent(this);
    m_Background->SetPosition(Vector::Vector2{20.0f, 380.0f});
    m_Background->SetScale(Vector::Vector2{1.0f, 10.0f});

    m_HighScoreLabel = new Texture("High score", "ModernDOS8x14.ttf", 22, SDL_Color{0xff, 0xff, 0xff});
    m_HighScoreLabel->SetParent(this);
    m_HighScoreLabel->SetPosition(Vector::VECTOR2_ZERO);

    m_ScoreLabel = new Texture("Score", "ModernDOS8x14.ttf", 22, SDL_Color{0xff, 0xff, 0xff});
    m_ScoreLabel->SetParent(this);
    m_ScoreLabel->SetPosition(Vector::Vector2{-27.0f, 56.0f});

    m_HighScoreBoard = new ScoreBoard();
    m_HighScoreBoard->SetParent(this);
    m_HighScoreBoard->SetPosition(Vector::Vector2{50.0f, 23.0f});

    m_ScoreBoard = new ScoreBoard();
    m_ScoreBoard->SetParent(this);
    m_ScoreBoard->SetPosition(Vector::Vector2{50.0f, 79.0f});
}

PlaySidebar::~PlaySidebar()
{
    m_Timer = nullptr;
    m_Audio = nullptr;
    delete m_Background;
    m_Background = nullptr;

    delete m_HighScoreLabel;
    m_HighScoreLabel = nullptr;

    delete m_ScoreLabel;
    m_ScoreLabel = nullptr;

    delete m_HighScoreBoard;
    m_HighScoreBoard = nullptr;

    delete m_ScoreBoard;
    m_ScoreBoard = nullptr;
}

void PlaySidebar::Update()
{

}

void PlaySidebar::Render()
{
    m_Background->Render();
    m_HighScoreLabel->Render();
    m_ScoreLabel->Render();
    m_HighScoreBoard->Render();
    m_ScoreBoard->Render();
}

void PlaySidebar::SetHighScore(int score)
{
    m_HighScoreBoard->SetScore(score);
}

void PlaySidebar::SetScore(int score)
{
    m_ScoreBoard->SetScore(score);
}