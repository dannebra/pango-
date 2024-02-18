#ifndef _INPUT_MANAGER_
#define _INPUT_MANAGER_

#include "SDL2/SDL.h"

using u8 = uint8_t;

class InputManager
{
    private:
        static InputManager *s_Instance;
        const u8 *m_KeyboardStates;
    
    public:
        static InputManager* Instance();
        static void Release();

        bool KeyDown(SDL_Scancode scancode);
        void Update();
    
    private:
        InputManager() = default;
        ~InputManager() {}
};

#endif