#ifndef _PLAY_SIDEBAR_H_
#define _PLAY_SIDEBAR_H_

#include "audio_manager.h"
#include "score_board.h"
#include "timer.h"

class PlaySidebar : public GameEntity
{
    public:
        PlaySidebar();
        ~PlaySidebar();
        void Update() override;
        void Render() override;

        void SetHighScore(int score);
        void SetScore(int score);
    private:
        Timer *m_Timer;
        AudioManager *m_Audio;
        Texture *m_Background;
        Texture *m_HighScoreLabel;
        Texture *m_ScoreLabel;

        ScoreBoard *m_HighScoreBoard;
        ScoreBoard *m_ScoreBoard;

};

#endif