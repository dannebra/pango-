#include "pango.h"
#include "gameloop.h"
#include "gui.h"
#include "input.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <cmath>
#include <stdio.h>
#include <string>

/*
    Play the game!
*/
int main(int argc, char *argv[])
{ 
    // ------------ Setup SDL ------------
    SDL_Window *window = nullptr;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
            pango::QuitWithError(window);
    } else {
        window = SDL_CreateWindow("Pango++", SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED, pango::screenWidth,
                                    pango::screenHeight, SDL_WINDOW_SHOWN);
        if (window == NULL) {
                printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
                pango::QuitWithError(window);
        } else {
                SDL_Surface *icon = IMG_Load("../assets/gui/pango.ico");
                if (icon == NULL) {
                  printf("Failed to load icon: %s\n", SDL_GetError());
                  pango::QuitWithError(window); 
                }

                SDL_SetWindowIcon(window, icon);
        }
    }

    SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL,
                SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
    
    SDL_Surface * titleScreen = pango::LoadSurface("../assets/gui/pango_title_screen.bmp", screenSurface->format);
    if (titleScreen == NULL) {
        printf("Failed to load stretching image!\n");
        pango::QuitWithError(window);
    }
    // ------------ Finished setting up SDL ------------

    pango::DrawTitleScreen(titleScreen, screenSurface, window);
    
    SDL_Event event;
    const u8 *keyboard = SDL_GetKeyboardState(NULL);
    pango::keyboard_inputs inputs{0, 0, 0, 0, 0, 0};
    do 
    {
        SDL_PumpEvents();

        // store player input
        inputs.keyW     = keyboard[SDL_SCANCODE_W];
        inputs.keyS     = keyboard[SDL_SCANCODE_S];
        inputs.keyA     = keyboard[SDL_SCANCODE_A];
        inputs.keyD     = keyboard[SDL_SCANCODE_D];
        inputs.keySpace = keyboard[SDL_SCANCODE_SPACE];
        inputs.keyP     = keyboard[SDL_SCANCODE_P];

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                {
                    SDL_FreeSurface(titleScreen);
                    SDL_FreeSurface(screenSurface);
                    pango::QuitWithSuccess(window);
                }
                case SDL_KEYDOWN:
                {
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        SDL_FreeSurface(titleScreen);
                        SDL_FreeSurface(screenSurface);
                        pango::QuitWithSuccess(window);
                    }
                    break;
                }
            }
        }

        SDL_UpdateWindowSurface(window);
    } while (pango::PangoLoop(inputs)); // TODO: pass input and renderer to gameloop
}


// Shut down SDL and reclaim resources. 
void pango::CleanupSDL(SDL_Window *window)
{
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void pango::QuitWithError(SDL_Window *window) {
    CleanupSDL(window);
    std::exit(EXIT_FAILURE);
}

void pango::QuitWithSuccess(SDL_Window *window) {
    CleanupSDL(window);
    std::exit(EXIT_SUCCESS);
}

