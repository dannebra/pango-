/**
 * This module handles functionality related to the graphical user interface.
*/

#include "gui.h"

/**
  * Load bitmap images as an SDL Surface
  * 
  * @param path bitmap image path
  * @param pixelFormat which pixel format to convert the surface to (@see SDL_PixelFormatEnum)
*/
SDL_Surface *pango::LoadSurface(const std::string &path, const SDL_PixelFormat *pixelFormat) {
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

/**
 * Draw the title screen
 * 
 * @param titleScreen - the title screen image
 * @param screenSurface - surface to stretch blit with
 * @param window - window to draw to
*/
void pango::DrawTitleScreen(SDL_Surface *titleScreen, SDL_Surface *screenSurface, SDL_Window *window)
{
    SDL_Rect stretchRect;
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = pango::screenWidth;
    stretchRect.h = pango::screenHeight;
    SDL_BlitScaled(titleScreen, NULL, screenSurface, &stretchRect);

    SDL_UpdateWindowSurface(window);
}