#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "game_entity.h"
#include "graphics.h"
#include <SDL2/SDL_image.h>
#include <string>

class Texture : public GameEntity
{
    private:
        SDL_Texture *m_Texture;
        Graphics *m_Graphics;

        int m_Width{};
        int m_Height{};
        SDL_Rect m_RenderRect;
    public:
        Texture() = delete;
        Texture(const std::string &filename);
        ~Texture();

        virtual void Render();
};

#endif