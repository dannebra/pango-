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
    SDL_Renderer *renderer = CreateRenderer(window);
    TTF_Font *font = SetupFont("../assets/font/ModernDOS8x14.ttf");
    SetupAudio();

    // ------------ Finished setting up SDL ------------

    SDL_Texture *background = IMG_LoadTexture(renderer, "../assets/gui/pango_title_screen.bmp");
    AudioManager audioManager{};
    audioManager.LoadMusic("../assets/audio/title_theme.mp3");
    audioManager.PlayMusic();

    SDL_Color textColor{255, 255 , 255};
    [[maybe_unused]] SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Test", textColor); // TODO: Draw text to screen

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
                    SDL_DestroyTexture(background);
                    QuitWithSuccess(window);
                }
                case SDL_KEYDOWN:
                {
                    SDL_Keycode pressedKey = event.key.keysym.sym;
                    if (pressedKey == SDLK_ESCAPE) {
                        SDL_DestroyTexture(background);
                        QuitWithSuccess(window);
                    } else if (pressedKey == SDLK_m) {
                        audioManager.ToggleMusic();
                    }

                    break;
                }
            }
        }

        //Update screen
        SDL_RenderCopy(renderer, background, NULL, NULL);
        SDL_RenderPresent(renderer);
    } while (PangoLoop(inputs)); // TODO: pass input and renderer to game loop

    return 0;
}