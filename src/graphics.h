#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Graphics
{
    public:
        static const int screenWidth = 640;
        static const int screenHeight = 480;

    private:
        bool m_Initialized = false;
        static Graphics *sInstance;
        SDL_Window *m_Window{};
        SDL_Renderer *m_Renderer{};
        bool Init();
        Graphics();

    public:
        static Graphics *Instance();
        bool HasInitialized();
        void FreeResources();
        SDL_Texture *LoadTexture(const std::string &path);
        void ClearBackBuffer();
        void DrawTexture(SDL_Texture *texture, const SDL_Rect *clip = nullptr, const SDL_Rect *rect = nullptr, const float angle = 0.0f, const SDL_RendererFlip flip = SDL_FLIP_NONE);
        SDL_Texture *CreateTextTexture(TTF_Font *font, const std::string &text, const SDL_Color color);
        void Render();
        
        ~Graphics();
};

#endif