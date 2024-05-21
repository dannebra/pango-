#ifndef _PLAY_SCREEN_H_
#define _PLAY_SCREEN_H_

#include "input_manager.h"
#include "game_entity.h"
#include "play_sidebar.h"
#include "timer.h"

class PlayScreen : public GameEntity
{
    public:
        PlayScreen();
        ~PlayScreen();
        void Render() override;
        void Update() override;

    private:
        Timer *m_Timer;
        InputManager *m_InputManager;
        PlaySidebar *m_PlaySidebar;

};

#endif