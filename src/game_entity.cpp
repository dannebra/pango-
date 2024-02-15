#include "game_entity.h"

GameEntity::GameEntity(float x, float y)
{
    m_Position.x = x;
    m_Position.y = y;

    m_Rotation = 0.0f;
    m_Active = true;
    m_Parent = nullptr;
}

GameEntity::~GameEntity()
{
    m_Parent = nullptr;
}

void GameEntity::SetPosition(Vector::Vector2 pos)
{
    m_Position = pos;
}

Vector::Vector2 GameEntity::GetPosition(Space space)
{
    if (space == Space::local || m_Parent == nullptr) {
        return m_Position;
    }

    return Vector::Add(m_Parent->GetPosition(Space::world), Vector::Rotate(m_Position, m_Parent->GetRotation(Space::local)));
}

void GameEntity::SetRotation(float rotation)
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
    // Update child's relative position to parent
    m_Position = Vector::Subtract(GetPosition(Space::world), m_Parent->GetPosition(Space::world));    
    m_Parent = parent;
}

GameEntity *GameEntity::GetParent()
{
    return m_Parent;
}

void GameEntity::Update() {}

void GameEntity::Render() {}