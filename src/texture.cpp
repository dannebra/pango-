#include "texture.h"
#include "asset_manager.h"
#include <stdio.h>
#include <string>

void Texture::Setup(const std::string &filename)
{
    m_Graphics = Graphics::Instance();
    m_Texture = AssetManager::Instance()->GetTexture(filename);
    if (m_Texture == NULL) {
        printf("Unable to load texture at: %s\n", filename.c_str());
    }
}

Texture::Texture(const std::string &filename)
{
    Setup(filename);
    SDL_QueryTexture(m_Texture, NULL, NULL, &m_Width, &m_Height);
    m_RenderRect.w = m_Width;
    m_RenderRect.h = m_Height;

    m_Clipped = false;
}

Texture::Texture(const std::string &filename, int x, int y, int width, int height)
{
    Setup(filename);
    m_Width = width;
    m_Height = height;

    m_RenderRect.w = width;
    m_RenderRect.h = height;

    m_ClippedRect.x = x;
    m_ClippedRect.y = y;
    m_ClippedRect.w = width;
    m_ClippedRect.h = height;

    m_Clipped = true;
}

Texture::Texture(const std::string &text, const std::string &fontPath, const int size, const SDL_Color color)
{
    m_Graphics = Graphics::Instance();
    m_Texture = AssetManager::Instance()->GetText(text, fontPath, size, color);

    m_Clipped = false;
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
    Vector::Vector2 scale = GetScale(Space::world);
    Vector::Vector2 position = GetPosition(Space::world);
    
    m_RenderRect.x = static_cast<int>(position.x - ((m_Width * scale.x) * 0.5f));
    m_RenderRect.y = static_cast<int>(position.y - ((m_Height * scale.y) * 0.5f));
    m_RenderRect.w = static_cast<int>(m_Width * scale.x);
    m_RenderRect.h = static_cast<int>(m_Height * scale.y);

    m_Graphics->DrawTexture(m_Texture, (m_Clipped) ? &m_ClippedRect : nullptr, &m_RenderRect, GetRotation(Space::world));
}