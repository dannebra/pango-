#ifndef _TIMER_H_
#define _TIMER_H_

#include <stdint.h>

class Timer
{
    private:
        static Timer *s_Instance;
        uint32_t m_StartTicks{};
        uint32_t m_ElapsedTicks{};
        float m_DeltaTime; // value in seconds
        float m_TimeScale;
    
    public:
        static Timer *Instance();
        static void FreeResources();
        void Reset();
        float DeltaTime();

        void SetTimeScale(float scale);
        float GetTimeScale();

        void Update();
    
    private:
        Timer();
        ~Timer();
};

#endif