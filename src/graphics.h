#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Graphics
{
    public:
        const int screenWidth = 640;
        const int screenHeight = 480;

    private:
        bool m_Initialized = false;
        static Graphics *sInstance;
        SDL_Window *m_Window{};
        SDL_Renderer *m_Renderer{};
        TTF_Font *m_Font{};
        bool Init();
        Graphics();
        
    public:
        static Graphics *Instance();
        bool HasInitialized();
        void FreeResources();
        SDL_Texture *LoadTexture(const std::string &path);
        void ClearBackBuffer();
        void Render();
        
        ~Graphics();
};

#endif