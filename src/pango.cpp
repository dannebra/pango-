/* ========================================================================

   Pango++ - a clone of the MS-DOS game Pango written in C++.
   
   @author Daniel Degirmen
   
   Title music: Cruising Down 8bit Lane - Monument_Music
   
   This software is provided 'as-is', without any express or implied
   warranty. In no event will the authors be held liable for any damages
   arising from the use of this software.

   ======================================================================== */

#include "gameloop.h"
#include "gui.h"
#include "init.h"
#include "input.h"
#include "audio_manager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <string>

/*
    Play the game!
*/
int main(int argc, char *argv[])
{ 
    // ------------ Setup SDL ------------
    SDL_Window *window = CreateWindow();
    SetupAudio();

    SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL,
                SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
    
    SDL_Surface *titleScreen = LoadSurface("../assets/gui/pango_title_screen.bmp", screenSurface->format);
    if (titleScreen == NULL) {
        QuitWithError(window);
    }
    // ------------ Finished setting up SDL ------------

    DrawTitleScreen(titleScreen, screenSurface, window);
    AudioManager audioManager{};
    audioManager.LoadMusic("../assets/audio/title_theme.mp3");
    audioManager.PlayMusic();
    
    SDL_Event event;
    const u8 *keyboard = SDL_GetKeyboardState(NULL);
    keyboard_inputs inputs{0, 0, 0, 0, 0, 0};
    
    do 
    {
        SDL_PumpEvents();

        // store player input
        inputs.keyW     = keyboard[SDL_SCANCODE_W];
        inputs.keyA     = keyboard[SDL_SCANCODE_A];
        inputs.keyS     = keyboard[SDL_SCANCODE_S];
        inputs.keyD     = keyboard[SDL_SCANCODE_D];
        inputs.keyP     = keyboard[SDL_SCANCODE_P];
        inputs.keySpace = keyboard[SDL_SCANCODE_SPACE];

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                {
                    SDL_FreeSurface(titleScreen);
                    SDL_FreeSurface(screenSurface);
                    QuitWithSuccess(window);
                }
                case SDL_KEYDOWN:
                {
                    SDL_Keycode pressedKey = event.key.keysym.sym;
                    if (pressedKey == SDLK_ESCAPE) {
                        SDL_FreeSurface(titleScreen);
                        SDL_FreeSurface(screenSurface);
                        QuitWithSuccess(window);
                    } else if (pressedKey == SDLK_m) {
                        audioManager.ToggleMusic();
                    }

                    break;
                }
            }
        }

        SDL_UpdateWindowSurface(window);
    } while (PangoLoop(inputs)); // TODO: pass input and renderer to game loop

    return 0;
}

