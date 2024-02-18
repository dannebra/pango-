#include "animated_texture.h"

AnimatedTexture::AnimatedTexture(const std::string &filename, Attributes attributes)
: Texture(filename, attributes.x, attributes.y, attributes.width, attributes.height)
{
    m_Timer = Timer::Instance();
    m_StartX = attributes.x;
    m_StartY = attributes.y;

    m_FrameCount = attributes.frameCount;
    m_AnimationSpeed = attributes.animationSpeed;
    m_TimePerFrame = attributes.animationSpeed / attributes.frameCount;
    m_AnimationTimer = 0.0f;
    m_AnimationDirection = attributes.direction;
    m_AnimationIsDone = false;
    m_WrapMode = WrapMode::loop;
}

void AnimatedTexture::SetWrapMode(WrapMode mode)
{
    m_WrapMode = mode;
}

void AnimatedTexture::Update()
{
    if (!m_AnimationIsDone) {
        m_AnimationTimer += m_Timer->DeltaTime();
    }

    if (m_AnimationTimer >= m_AnimationSpeed) {
        if (m_WrapMode == WrapMode::loop) {
            m_AnimationTimer -= m_AnimationSpeed; // wrap back to 0
        } else {
            m_AnimationIsDone = true;
            m_AnimationTimer = m_AnimationSpeed - m_TimePerFrame; // step back 1 frame
        }
    }

    if (m_AnimationDirection == AnimationDirection::horizontal) {
        m_ClippedRect.x = m_StartX + (static_cast<int>(m_AnimationTimer / m_TimePerFrame) * m_Width);
    } else {
        m_ClippedRect.y = m_StartY + (static_cast<int>(m_AnimationTimer / m_TimePerFrame) * m_Height);
    }
}