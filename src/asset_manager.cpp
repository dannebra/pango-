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

void AssetManager::Release()
{
    delete s_AssetManager;
    s_AssetManager = nullptr;
}

AssetManager::~AssetManager()
{
    for (auto values : m_Textures) {
        SDL_DestroyTexture(values.second);
    }

    m_Textures.clear();
}

SDL_Texture *AssetManager::GetTexture(const std::string &filename)
{
    std::string texturePath{SDL_GetBasePath()};
    texturePath.append("assets/" + filename);

    if (m_Textures[texturePath] == nullptr) {
        m_Textures[texturePath] = Graphics::Instance()->LoadTexture(texturePath);
    }

    return m_Textures[texturePath];
}