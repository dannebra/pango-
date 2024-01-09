#include "gui.h"

/**
 * Draw the title screen
 * 
 * @param titleScreen - the title screen image
 * @param screenSurface - surface to stretch blit with
 * @param window - window to draw to
*/
void DrawTitleScreen(SDL_Surface *titleScreen, SDL_Surface *screenSurface, SDL_Window *window)
{
    SDL_Rect stretchRect;
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = pango_gui::screenWidth;
    stretchRect.h = pango_gui::screenHeight;
    SDL_BlitScaled(titleScreen, NULL, screenSurface, &stretchRect);

    SDL_UpdateWindowSurface(window);
}
