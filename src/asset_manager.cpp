#include "asset_manager.h"
#include "graphics.h"

AssetManager* AssetManager::sAssetManager{nullptr};

AssetManager *AssetManager::Instance()
{
    if (!sAssetManager) {
        sAssetManager = new AssetManager();
    }

    return sAssetManager;
}

void AssetManager::Release()
{
    delete sAssetManager;
    sAssetManager = nullptr;
}

AssetManager::~AssetManager()
{
    for (auto values : m_textures) {
        SDL_DestroyTexture(values.second);
    }

    m_textures.clear();
}

SDL_Texture *AssetManager::GetTexture(const std::string &filename)
{
    std::string texturePath{SDL_GetBasePath()};
    texturePath.append("assets/" + filename);

    if (m_textures[texturePath] == nullptr) {
        m_textures[texturePath] = Graphics::Instance()->LoadTexture(texturePath);
    }

    return m_textures[texturePath];
}