#include "asset_manager.h"
#include "graphics.h"

AssetManager* AssetManager::s_AssetManager{nullptr};

AssetManager *AssetManager::Instance()
{
    if (!s_AssetManager) {
        s_AssetManager = new AssetManager();
    }

    return s_AssetManager;
}

void AssetManager::FreeResources()
{
    delete s_AssetManager;
    s_AssetManager = nullptr;
}

AssetManager::~AssetManager()
{
    for (auto texture : m_Textures) {
        SDL_DestroyTexture(texture.second);
    }
    m_Textures.clear();

    for (auto text : m_TextTextures) {
        SDL_DestroyTexture(text.second);
    }
    m_TextTextures.clear();

    for (auto font : m_Fonts) {
        TTF_CloseFont(font.second);
    }
    m_Fonts.clear();
}

SDL_Texture *AssetManager::GetTexture(const std::string &filename)
{
    std::string texturePath{SDL_GetBasePath()};
    texturePath.append("../assets/gui/" + filename);

    if (m_Textures[texturePath] == nullptr) {
        m_Textures[texturePath] = Graphics::Instance()->LoadTexture(texturePath);
    }

    return m_Textures[texturePath];
}

TTF_Font *AssetManager::GetFont(const std::string &filename, const int size)
{
    std::string fontPath{SDL_GetBasePath()};
    fontPath.append("../assets/font/" + filename);

    std::string key = fontPath + std::to_string(size);
    if (m_Fonts[key] == nullptr) {
        m_Fonts[key] = TTF_OpenFont(fontPath.c_str(), size);
        
        if (m_Fonts[key] == nullptr) {
            printf("Font Loading Error: Font: %s, Error: %s", filename.c_str(), TTF_GetError());
        }
    }

    return m_Fonts[key];
}

SDL_Texture *AssetManager::GetText(const std::string &text, const std::string &filename, const int size, const SDL_Color color)
{
    TTF_Font *font = GetFont(filename, size);
    std::string key = text + filename + std::to_string(size) + std::to_string(color.r) + std::to_string(color.g) + std::to_string(color.b);
    if (m_TextTextures[key] == nullptr) {
        m_TextTextures[key] = Graphics::Instance()->CreateTextTexture(font, text, color);
    }

    return m_TextTextures[key];
}