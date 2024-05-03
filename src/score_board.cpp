#include "score_board.h"

ScoreBoard::ScoreBoard()
{
    SetScore(0);
}

ScoreBoard::~ScoreBoard()
{
    ClearBoard();
}

void ScoreBoard::ClearBoard()
{
    for (std::size_t i = 0; i < m_Score.size(); i++) {
        delete m_Score[i];
        m_Score[i] = nullptr;
    }
    m_Score.clear();
}

void ScoreBoard::SetScore(int score)
{
    ClearBoard();
    std::string scoreString{std::to_string(score)};
    std::size_t lastIndex = scoreString.length() - 1;

    for (std::size_t i = 0; i <= lastIndex; i++) {
        m_Score.push_back(new Texture(scoreString.substr(i, 1), "ModernDOS8x14.ttf", 22, SDL_Color{0xff, 0xff, 0xff}));
        m_Score[i]->SetParent(this);
        m_Score[i]->SetPosition(Vector::Vector2(-12.0f * (lastIndex - i), 0.0f));
    }
}

void ScoreBoard::Render()
{
    for (auto number : m_Score) {
        number->Render();
    }
}