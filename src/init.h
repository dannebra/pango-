#ifndef _PANGO_INIT_H_
#define _PANGO_INIT_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

SDL_Window *CreateWindow();
SDL_Renderer *CreateRenderer(SDL_Window *window);
void SetupAudio();
TTF_Font *SetupFont(const std::string &fontPath);
void CleanupSDL(SDL_Window *window);
void QuitWithError(SDL_Window *window);
void QuitWithSuccess(SDL_Window *window);

#endif