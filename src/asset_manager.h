#ifndef _ASSET_MANAGER_H_
#define _ASSET_MANAGER_H_

#include "graphics.h"
#include <cstdio>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <unordered_map>

class AssetManager
{
    private:
        static AssetManager *s_AssetManager;
        // base textures
        std::unordered_map<std::string, SDL_Texture*> m_Textures{};

        // text
        std::unordered_map<std::string, SDL_Texture*> m_TextTextures{};
        std::unordered_map<std::string, TTF_Font*> m_Fonts{};

        // music and sound
        std::unordered_map<std::string, Mix_Music*> m_Music{};
        std::unordered_map<std::string, Mix_Chunk*> m_Sfx{};

    public:
        static AssetManager *Instance();
        static void FreeResources();
        SDL_Texture *GetTexture(const std::string &filename);
        SDL_Texture *GetText(const std::string &text, const std::string &filename, const int size, const SDL_Color color);
    
        Mix_Music *GetMusic(const std::string &filename);
        Mix_Chunk *GetSfx(const std::string &filename);

        inline static const std::string GUI_PATH = "../assets/gui/";
        inline static const std::string AUDIO_PATH = "../assets/audio/";
        inline static const std::string FONT_PATH = "../assets/font/";
        inline static const std::string SPRITE_PATH = "../assets/sprite-images/";

    private:
        AssetManager() = default;
        ~AssetManager();

        TTF_Font *GetFont(const std::string &filename, const int size);
};

#endif