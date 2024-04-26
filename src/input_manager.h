#ifndef _INPUT_MANAGER_
#define _INPUT_MANAGER_

#include "game_math.h"
#include <memory>
#include <SDL2/SDL.h>
#include <string>


using u8 = uint8_t;
using u32 = uint32_t;

class InputManager
{
    public:
        enum class MouseButton
        {
            left,
            right,
            middle,
            back,
            forward,
        };

    private:
        static InputManager *s_Instance;
        const u8 *m_KeyboardState;
        std::unique_ptr<u8[]> m_PreviousKeyboardState;
        int m_KeyLength;

        u32 m_MouseState;
        u32 m_PreviousMouseState;

        int m_MousePositionX;
        int m_MousePositionY;
    
    public:
        static InputManager* Instance();
        static void FreeResources();

        bool KeyDown(SDL_Scancode scancode);
        bool KeyPressed(SDL_Scancode scancode);
        bool KeyReleased(SDL_Scancode scancode);

        Vector::Vector2 GetMousePosition();
        bool MouseButtonDown(MouseButton button);
        bool MouseButtonPressed(MouseButton button);
        bool MouseButtonReleased(MouseButton button);

        void Update();
        void UpdatePreviousInput();
    
    private:
        InputManager();
        ~InputManager();

        u32 GetMouseMask(MouseButton button);
};

#endif