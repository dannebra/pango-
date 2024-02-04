#include "timer.h"
#include <SDL2/SDL.h>

Timer *Timer::s_Instance = nullptr;

Timer *Timer::Instance()
{
    if (s_Instance == nullptr) {
        s_Instance = new Timer();
    }

    return s_Instance;
}

void Timer::FreeResources()
{
    delete s_Instance;
    s_Instance = nullptr;
}

void Timer::Reset()
{
    m_StartTicks = SDL_GetTicks();
    m_ElapsedTicks = 0;
    m_DeltaTime = 0.0f;
}

float Timer::DeltaTime()
{
    return m_DeltaTime;
}

void Timer::SetTimeScale(float scale)
{
    m_TimeScale = scale;
}

float Timer::GetTimeScale()
{
    return m_TimeScale;
}

void Timer::Update()
{
    m_ElapsedTicks = SDL_GetTicks() - m_StartTicks;
    m_DeltaTime = m_ElapsedTicks * 0.001f;
}

Timer::Timer()
{
    Reset();
    m_TimeScale = 1.0f;
}

Timer::~Timer()
{

}