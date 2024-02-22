#ifndef _ASSET_MANAGER_H_
#define _ASSET_MANAGER_H_

#include "graphics.h"
#include <SDL2/SDL_image.h>
#include <unordered_map>

class AssetManager
{
    private:
        static AssetManager *s_AssetManager;
        std::unordered_map<std::string, SDL_Texture*> m_Textures;
        std::unordered_map<std::string, SDL_Texture*> m_TextTextures;
        std::unordered_map<std::string, TTF_Font*> m_Fonts;

    public:
        static AssetManager *Instance();
        static void FreeResources();
        SDL_Texture *GetTexture(const std::string &filename);
        SDL_Texture *GetText(const std::string &text, const std::string &filename, const int size, const SDL_Color color);
    
    private:
        AssetManager() = default;
        ~AssetManager();

        TTF_Font *GetFont(const std::string &filename, const int size);
};

#endif