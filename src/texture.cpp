#include "texture.h"
#include "asset_manager.h"
#include <stdio.h>
#include <string>

Texture::Texture(const std::string &filename)
{
    m_Graphics = Graphics::Instance();
    m_Texture = AssetManager::Instance()->GetTexture(filename);
    if (m_Texture == NULL) {
        printf("Unable to load texture at: %s\n", filename.c_str());
    }

    SDL_QueryTexture(m_Texture, NULL, NULL, &m_Width, &m_Height);
    m_RenderRect.w = m_Width;
    m_RenderRect.h = m_Height;
}

Texture::~Texture()
{
    m_Graphics = nullptr;
    m_Texture = nullptr;
}

void Texture::Render()
{
    Vector::Vector2 position = GetPosition(Space::world);
    m_RenderRect.x = static_cast<int>(position.x - (m_Width * 0.5f));
    m_RenderRect.y = static_cast<int>(position.y - (m_Height * 0.5f));
    // printf("x: %d, y: %d\n", m_RenderRect.x, m_RenderRect.y);
    m_Graphics->DrawTexture(m_Texture, &m_RenderRect);
}