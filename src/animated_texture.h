#ifndef _ANINMATED_TEXTURE_
#define _ANINMATED_TEXTURE_

#include "timer.h"
#include "texture.h"
#include <string>

class AnimatedTexture : public Texture
{
    public:
        enum class WrapMode 
        {
            once, // animate once
            loop, // loop animation
        };

        enum class AnimationDirection
        {
            horizontal,
            vertical,
        };

        struct Attributes
        {
            int x;
            int y; 
            int width; 
            int height; 
            int frameCount; 
            float animationSpeed;
            AnimationDirection direction;
        };

    private:
        Timer *m_Timer;
        
        int m_StartX;
        int m_StartY;

        float m_AnimationTimer;
        float m_AnimationSpeed;
        float m_TimePerFrame;

        int m_FrameCount;
        
        WrapMode m_WrapMode;
        AnimationDirection m_AnimationDirection;

        bool m_AnimationIsDone;
    
    public:
        AnimatedTexture(const std::string &filename, const Attributes attributes);
        AnimatedTexture(const std::string &filename, const std::string &fontPath, const int size, const SDL_Color color, const Attributes attributes);
        ~AnimatedTexture() = default;

        void SetWrapMode(WrapMode mode);
        virtual void Update() override;
};

#endif