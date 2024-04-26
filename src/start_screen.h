#ifndef _START_SCREEN_H_
#define _START_SCREEN_H_

#include "animated_texture.h"
#include "input_manager.h"

class StartScreen : public GameEntity
{
    private:
        enum class SelectedMode
        {
            start,
            options,
        };
    public:
        StartScreen();
        virtual ~StartScreen();
        void Update() override; 
        void Render() override;
        void ChangeSelectedMode();
    
    private:
        GameEntity *m_TopBar;
        Texture *m_HighScore;

        AnimatedTexture *m_Logo;

        GameEntity *m_Selections;
        Texture *m_StartGameText;
        Texture *m_OptionsText;
        Texture *m_Cursor;

        SelectedMode m_SelectedMode;
        Vector::Vector2 m_CursorStartPosition;
        Vector::Vector2 m_CursorOffset;

        InputManager *m_Input;
};


#endif

