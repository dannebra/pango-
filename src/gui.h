#ifndef _PANGO_GUI_H_
#define _PANGO_GUI_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <string>

namespace pango
{
    constexpr int screenWidth = 640;
    constexpr int screenHeight = 480;

    SDL_Surface *LoadSurface(const std::string path, const SDL_PixelFormat *screenSurface);
    void DrawTitleScreen(SDL_Surface *titleScreen, SDL_Surface *screenSurface, SDL_Window *window);
}

#endif