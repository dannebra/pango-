#include "init.h"
#include "gui.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>

/**
 * Create an SDL window to draw to
*/
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

/**
 * Setup the audio handling.
*/
void SetupAudio()
{
    constexpr int frequency = 44100;
    constexpr int channels = 2; // stereo
    constexpr int sampleSize = 2048; // 2 KiB
    if (Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, channels, sampleSize) < 0 ) { // Should this be handled? Do we care if we have no sound? 
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

/**
 * Load bitmap images as an SDL Surface
 * 
 * @param path bitmap image path
 * @param pixelFormat which pixel format to convert the surface to (@see SDL_PixelFormatEnum)
*/
SDL_Surface *LoadSurface(const std::string &path, const SDL_PixelFormat *pixelFormat)
{
    SDL_Surface *optimizedSurface = NULL;

    SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == NULL) {
      printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    } else {
      optimizedSurface = SDL_ConvertSurface(loadedSurface, pixelFormat, 0);
      
      if (optimizedSurface == NULL) {
        printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
      }

      SDL_FreeSurface(loadedSurface); // reclaim resources from unoptimized surface
    }

    return optimizedSurface;
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
