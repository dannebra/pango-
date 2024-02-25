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
    Vector::Vector2 rotationPosition = Vector::Rotate(m_Position, m_Parent->GetRotation(Space::local));

    return Vector::Add(m_Parent->GetPosition(Space::world),
                       Vector::Vector2(rotationPosition.x * parentScale.x, rotationPosition.y * parentScale.y));
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
    Vector::Vector2 parentScale = m_Parent->GetScale(Space::world);

    return Vector::Vector2(parentScale.x * m_Scale.x, parentScale.y * m_Scale.y);
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
    if (this == parent) {
        m_Parent = nullptr;
        return;
    }
    
    m_Parent = parent;
    // Update child's relative position to parent
    m_Position = Vector::Subtract(GetPosition(Space::world), m_Parent->GetPosition(Space::world));     
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