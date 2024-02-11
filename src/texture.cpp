#include "texture.h"
#include <stdio.h>
#include <string>

Texture::Texture(const std::string &path)
{
    m_Graphics = Graphics::Instance();
    m_Texture = m_Graphics->LoadTexture(path);
    if (m_Texture == NULL) {
        printf("Unable to load texture at: %s\n", path.c_str());
    }
}

Texture::~Texture()
{
    SDL_DestroyTexture(m_Texture);
    m_Graphics = nullptr;
    m_Texture = nullptr;
}

void Texture::Render()
{
    m_Graphics->DrawTexture(m_Texture);
}