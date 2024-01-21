/* ========================================================================

   Pango++ - a clone of the MS-DOS game Pango written in C++.
   
   @author Daniel Degirmen
   
   Title music: Cruising Down 8bit Lane - Monument_Music
   
   This software is provided 'as-is', without any express or implied
   warranty. In no event will the authors be held liable for any damages
   arising from the use of this software.

   ======================================================================== */

#include "asset_manager.h"
#include "audio_manager.h"
#include "gameloop.h"
#include "graphics.h"
#include "input.h"
#include "texture.h"
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
    // ------------ Setup subsystems ------------
    Graphics *graphics = Graphics::Instance();
    graphics->Init();

    AudioManager audioManager{};
    // ------------ Finished setting up subsystems ------------


    audioManager.LoadMusic("../assets/audio/title_theme.mp3");
    audioManager.PlayMusic();

    SDL_Event event;
    const u8 *keyboard = SDL_GetKeyboardState(NULL);
    keyboard_inputs inputs{};
    
    do 
    {
        SDL_PumpEvents();
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
                    std::exit(EXIT_SUCCESS); // TODO: Cleanup before exiting
                }
                case SDL_KEYDOWN:
                {
                    SDL_Keycode pressedKey = event.key.keysym.sym;
                    if (pressedKey == SDLK_ESCAPE) {
                        std::exit(EXIT_SUCCESS); // TODO: Cleanup before exiting
                    } else if (pressedKey == SDLK_m) {
                        audioManager.ToggleMusic();
                    }

                    break;
                }
            }
        }

        graphics->ClearBackBuffer();
        graphics->Render();
    } while (PangoLoop(inputs)); // TODO: pass input and renderer to game loop

    return 0;
}