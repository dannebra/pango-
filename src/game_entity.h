#ifndef _GAME_ENTITY_
#define _GAME_ENTITY_

#include "game_math.h"

/**
 * Base class for all our game entities
*/
class GameEntity
{
    public:
        enum class Space
        {
            local,
            world,
        };
    private:
        Vector::Vector2 m_Position{};
        Vector::Vector2 m_Scale{};
        float m_Rotation{};
        bool m_Active{};
        GameEntity *m_Parent{};

    public:
        GameEntity(float x = 0.0f, float y = 0.0f);
        ~GameEntity();

        void SetPosition(const Vector::Vector2 pos);
        Vector::Vector2 GetPosition(Space space = Space::world);

        void SetScale(const Vector::Vector2 scale);
        Vector::Vector2 GetScale(Space space = Space::world);

        void SetRotation(const float rotation);
        float GetRotation(Space space = Space::world);
        
        void SetActive(bool active);
        bool GetActive();
        
        void SetParent(GameEntity *parent);
        GameEntity *GetParent();

        void Translate(Vector::Vector2 vector);
        void Rotate(const float amount);

        virtual void Update();
        virtual void Render();
};

#endif