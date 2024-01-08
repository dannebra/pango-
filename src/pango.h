#ifndef _PANGO_H_
#define _PANGO_H_

#include <SDL2/SDL.h>

namespace pango
{
    void CleanupSDL(SDL_Window *window);
    void QuitWithError(SDL_Window *window);
    void QuitWithSuccess(SDL_Window *window);
}
#endif