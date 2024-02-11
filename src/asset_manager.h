#ifndef _ASSET_MANAGER_H_
#define _ASSET_MANAGER_H_

#include <SDL2/SDL_image.h>
#include <unordered_map>

class AssetManager
{
    private:
        static AssetManager *s_AssetManager;
        std::unordered_map<std::string, SDL_Texture*> m_Textures;

    public:
        static AssetManager *Instance();
        static void Release();
        SDL_Texture *GetTexture(const std::string &filename);
    
    private:
        AssetManager() = default;
        ~AssetManager();
};

#endif