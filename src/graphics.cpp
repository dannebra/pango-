#include "graphics.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

Graphics *Graphics::sInstance{nullptr};

Graphics *Graphics::Instance()
{
    if (!sInstance) {
        sInstance = new Graphics();
    }

    return sInstance;
}
        
bool Graphics::Init()
{
    // Create the window to draw to
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    } else {
        m_Window = SDL_CreateWindow("Pango++", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                    screenWidth, screenHeight, SDL_WINDOW_SHOWN);
        if (m_Window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            return false;
        } else {
            SDL_Surface *icon = IMG_Load("../assets/gui/pango.ico");
            if (icon == NULL) {
                printf("Failed to load icon: %s\n", SDL_GetError());
                return false;
            }

            SDL_SetWindowIcon(m_Window, icon);
        }
    }

    // Create renderer
    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
    if (m_Renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    SDL_SetRenderDrawColor(m_Renderer, 0x0, 0x0, 0x0, 0x0); // black with full opacity

    // Initialize image loading
    int imageFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imageFlags) & imageFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    // Initialize ttf library
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }
    TTF_OpenFont("../assets/font/ModernDOS8x14.ttf", 28);

    return true;
}

SDL_Texture *Graphics::LoadTexture(const std::string &path)
{
    return IMG_LoadTexture(m_Renderer, path.c_str());
}

void Graphics::ClearBackBuffer()
{
    SDL_RenderClear(m_Renderer);
}

void Graphics::Render()
{
    SDL_RenderPresent(m_Renderer);
}

bool Graphics::HasInitialized()
{
    return m_Initialized;
}

void Graphics::FreeResources()
{
    SDL_DestroyWindow(m_Window);
    m_Window = nullptr;

    SDL_DestroyRenderer(m_Renderer);
    m_Renderer = nullptr;

    TTF_CloseFont(m_Font);
    m_Font = nullptr;

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

Graphics::Graphics()
{
    m_Initialized = Init();
}

Graphics::~Graphics()
{
    FreeResources();
}