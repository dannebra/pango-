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
#include "game_manager.h"
#include "graphics.h"
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
    GameManager *pango = GameManager::Instance();
    pango->Run();

    GameManager::ShutdownGame();
    pango = nullptr;

    return 0;
}