#ifndef _SCORE_BOARD_H_
#define _SCORE_BOARD_H_

#include "texture.h"
#include <vector>

class ScoreBoard : public GameEntity
{
    public:
        ScoreBoard();
        virtual ~ScoreBoard();

        void SetScore(int score);
        virtual void Render() override;

        
    private:
        std::vector<Texture*> m_Score{};

        void ClearBoard();

};

#endif