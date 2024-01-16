#include "init.h"
#include "gui.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>

SDL_Window *CreateWindow()
{
    SDL_Window *window = nullptr;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        std::exit(EXIT_FAILURE);
    } else {
        window = SDL_CreateWindow("Pango++", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  pango_gui::screenWidth, pango_gui::screenHeight, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            QuitWithError(window);
        } else {
            SDL_Surface *icon = IMG_Load("../assets/gui/pango.ico");
            
            if (icon == NULL) {
                printf("Failed to load icon: %s\n", SDL_GetError());
                QuitWithError(window); 
            }

            SDL_SetWindowIcon(window, icon);
        }
    }

    return window;
}

SDL_Renderer *CreateRenderer(SDL_Window *window)
{
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        QuitWithError(window);
    }

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); // (rgba) white text with full opacity
    return renderer;
}

void SetupAudio()
{
    constexpr int frequency = 44100;
    constexpr int channels = 2; // stereo
    constexpr int sampleSize = 2048; // 2 KiB
    if (Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, channels, sampleSize) < 0 ) { // Should this be handled? Do we care if we have no sound? 
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

TTF_Font *SetupFont(const std::string &fontPath)
{
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return nullptr;
    }

    constexpr int fontSize = 28;
    return TTF_OpenFont(fontPath.c_str(), fontSize);
}


void CleanupSDL(SDL_Window *window)
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void QuitWithError(SDL_Window *window)
{
    CleanupSDL(window);
    std::exit(EXIT_FAILURE);
}

void QuitWithSuccess(SDL_Window *window)
{
    CleanupSDL(window);
    std::exit(EXIT_SUCCESS);
}
