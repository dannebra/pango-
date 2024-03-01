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

    for (auto music : m_Music) {
        Mix_FreeMusic(music.second);
    }
    m_Music.clear();

    for (auto sfx : m_Sfx) {
        Mix_FreeChunk(sfx.second);
    }
    m_Sfx.clear();
}

SDL_Texture *AssetManager::GetTexture(const std::string &filename)
{
    char *basePath = SDL_GetBasePath();
    std::string texturePath{basePath};
    texturePath.append(GUI_PATH + filename);

    if (m_Textures[texturePath] == nullptr) {
        m_Textures[texturePath] = Graphics::Instance()->LoadTexture(texturePath);
    }
    SDL_free(basePath);

    return m_Textures[texturePath];
}

TTF_Font *AssetManager::GetFont(const std::string &filename, const int size)
{
    char *basePath = SDL_GetBasePath();
    std::string fontPath{basePath};
    fontPath.append(FONT_PATH + filename);

    std::string key = fontPath + std::to_string(size);
    if (m_Fonts[key] == nullptr) {
        m_Fonts[key] = TTF_OpenFont(fontPath.c_str(), size);
        
        if (m_Fonts[key] == nullptr) {
            printf("Font Loading Error: Font: %s, Error: %s\n", filename.c_str(), TTF_GetError());
        }
    }
    SDL_free(basePath);

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

Mix_Music *AssetManager::GetMusic(const std::string &filename)
{
    char *basePath = SDL_GetBasePath();
    std::string audioPath{basePath};
    audioPath.append(AUDIO_PATH + filename);

    if (m_Music[filename] == nullptr) {
        m_Music[filename] = Mix_LoadMUS(audioPath.c_str());
        
        if (m_Music[filename] == nullptr) {
            printf("Music Loading Error: File: %s, Error: %s\n", filename.c_str(), Mix_GetError());
        }
    }
    SDL_free(basePath);

    return m_Music[filename];
}
        
Mix_Chunk *AssetManager::GetSfx(const std::string &filename)
{
    char *basePath = SDL_GetBasePath();
    std::string audioPath{basePath};
    audioPath.append("../assets/audio/" + filename);

    if (m_Sfx[filename] == nullptr) {
        m_Sfx[filename] = Mix_LoadWAV(audioPath.c_str());
        
        if (m_Sfx[filename] == nullptr) {
            printf("Sfx Loading Error: File: %s, Error: %s\n", filename.c_str(), Mix_GetError());
        }
    }
    SDL_free(basePath);

    return m_Sfx[filename];
}