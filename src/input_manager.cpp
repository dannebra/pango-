#include "input_manager.h"
#include <memory>

InputManager *InputManager::s_Instance = nullptr;

InputManager::InputManager()
{
    m_KeyboardState = SDL_GetKeyboardState(&m_KeyLength);
    m_PreviousKeyboardState = std::make_unique<u8[]>(m_KeyLength);

    memcpy(m_PreviousKeyboardState.get(), m_KeyboardState, m_KeyLength);
}

InputManager::~InputManager()
{
    m_PreviousKeyboardState = nullptr;
}

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
    return m_KeyboardState[scancode];
}

bool InputManager::KeyPressed(SDL_Scancode scancode)
{
    return (!m_PreviousKeyboardState[scancode]) && (m_KeyboardState[scancode]);
}

bool InputManager::KeyReleased(SDL_Scancode scancode)
{
    return (m_PreviousKeyboardState[scancode]) && (!m_KeyboardState[scancode]);
}

Vector::Vector2 InputManager::GetMousePosition()
{
    return Vector::Vector2{static_cast<float>(m_MousePositionX), static_cast<float>(m_MousePositionY)};
}

u32 InputManager::GetMouseMask(MouseButton button)
{
    u32 mouseMask = 0;
    switch (button)
    {
    case MouseButton::left:
        mouseMask = SDL_BUTTON_LMASK;
        break;
    case MouseButton::right:
        mouseMask = SDL_BUTTON_RMASK;
        break;
    case MouseButton::middle:
        mouseMask = SDL_BUTTON_MMASK;
        break;
    case MouseButton::back:
        mouseMask = SDL_BUTTON_X1MASK;
        break;
    case MouseButton::forward:
        mouseMask = SDL_BUTTON_X2MASK;
        break;
    }

    return mouseMask;
}

bool InputManager::MouseButtonDown(MouseButton button)
{
    return (m_MouseState & GetMouseMask(button));
}

bool InputManager::MouseButtonPressed(MouseButton button)
{
    u32 mouseMask = GetMouseMask(button);
    return !(m_PreviousMouseState & mouseMask) && (m_MouseState & mouseMask);
}

bool InputManager::MouseButtonReleased(MouseButton button)
{
    u32 mouseMask = GetMouseMask(button);
    return (m_PreviousMouseState & mouseMask) && !(m_MouseState & mouseMask);
}

void InputManager::Update()
{
    m_MouseState = SDL_GetMouseState(&m_MousePositionX, &m_MousePositionY);
}

void InputManager::UpdatePreviousInput()
{
    memcpy(m_PreviousKeyboardState.get(), m_KeyboardState, m_KeyLength);
    m_PreviousMouseState = m_MouseState;
}