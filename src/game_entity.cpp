#include "game_entity.h"

GameEntity::GameEntity(float x, float y)
{
    m_Position.x = x;
    m_Position.y = y;

    m_Scale = Vector::VECTOR2_ONE;
    m_Rotation = 0.0f;

    m_Active = true;
    m_Parent = nullptr;
}

GameEntity::GameEntity(Vector::Vector2 position) : GameEntity(position.x, position.y) {}

GameEntity::~GameEntity()
{
    m_Parent = nullptr;
}

void GameEntity::SetPosition(const Vector::Vector2 pos)
{
    m_Position = pos;
}

Vector::Vector2 GameEntity::GetPosition(Space space)
{
    if (space == Space::local || m_Parent == nullptr) {
        return m_Position;
    }
    Vector::Vector2 parentScale = m_Parent->GetScale(Space::world);
    Vector::Vector2 rotationPosition = Vector::Rotate(Vector::Vector2{m_Position.x * parentScale.x, m_Position.y * parentScale.y},
                                                      m_Parent->GetRotation(Space::local));

    return Vector::Add(m_Parent->GetPosition(Space::world), rotationPosition);
}

void GameEntity::SetScale(const Vector::Vector2 scale)
{
    m_Scale = scale;
}

Vector::Vector2 GameEntity::GetScale(Space space)
{
    if (space == Space::local || m_Parent == nullptr) {
        return m_Scale;
    }
    
    Vector::Vector2 scale = m_Parent->GetScale(Space::world);
    scale.x *= m_Scale.x;
    scale.y *= m_Scale.y;

    return scale;
}

void GameEntity::SetRotation(const float rotation)
{
    m_Rotation = rotation;

    if (m_Rotation > 360.0f) { // Keep rotation between 0 and 360 degrees
        int mul = m_Rotation / 360;
        m_Rotation -= 360.0f * mul;
    } else if (m_Rotation < 0.0f) {
        int mul = (m_Rotation / 360) - 1;
        m_Rotation -= 360.0f * mul;
    }
}

float GameEntity::GetRotation(Space space)
{
    if (space == Space::local || m_Parent == nullptr) {
        return m_Rotation;
    }

    return m_Parent->GetRotation(Space::world) + m_Rotation;
}

void GameEntity::SetActive(bool active)
{
    m_Active = active;
}

bool GameEntity::GetActive()
{
    return m_Active;
}

void GameEntity::SetParent(GameEntity *parent)
{
    if (parent == nullptr) {
        m_Position = GetPosition(Space::world);
        m_Rotation = GetRotation(Space::world);
        m_Scale = GetScale(Space::world);
    } else {
        if (m_Parent != nullptr) {
            SetParent(nullptr);
        }

        m_Position = Vector::Rotate(Vector::Subtract(GetPosition(Space::world), parent->GetPosition(Space::world)),
                                    -(parent->GetRotation(Space::world)));

        Vector::Vector2 parentScale = parent->GetScale(Space::world);
        m_Position.x /= parentScale.x;
        m_Position.y /= parentScale.y;

        m_Rotation -= parent->GetRotation(Space::world);
        m_Scale = Vector::Vector2(m_Scale.x / parentScale.x, m_Scale.y / parentScale.y);
    }

    m_Parent = parent;
}

GameEntity *GameEntity::GetParent()
{
    return m_Parent;
}

void GameEntity::Translate(Vector::Vector2 offset)
{
    m_Position.Add(offset);
}

void GameEntity::Rotate(const float amount)
{
    m_Rotation += amount;
}

void GameEntity::Update() {}

void GameEntity::Render() {}