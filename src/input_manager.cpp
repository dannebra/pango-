#include "input_manager.h"

InputManager *InputManager::s_Instance = nullptr;

InputManager *InputManager::Instance()
{
    if (s_Instance == nullptr) {
        s_Instance = new InputManager();
    }

    return s_Instance;
}

void InputManager::FreeResources()
{
    delete s_Instance;
    s_Instance = nullptr;
}

bool InputManager::KeyDown(SDL_Scancode scancode)
{
    return m_KeyboardStates[scancode];
}

void InputManager::Update()
{
    m_KeyboardStates = SDL_GetKeyboardState(NULL);
}