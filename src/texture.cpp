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
}

Texture::~Texture()
{
    m_Graphics = nullptr;
    m_Texture = nullptr;
}

void Texture::Render()
{
    m_Graphics->DrawTexture(m_Texture);
}