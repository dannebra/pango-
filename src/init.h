#ifndef _PANGO_INIT_H_
#define _PANGO_INIT_H_

#include <SDL2/SDL.h>
#include <string>

SDL_Window *CreateWindow();
SDL_Surface *LoadSurface(const std::string &path, const SDL_PixelFormat *screenSurface);
void CleanupSDL(SDL_Window *window);
void QuitWithError(SDL_Window *window);
void QuitWithSuccess(SDL_Window *window);

#endif