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
    public:
        Texture() = delete;
        Texture(const std::string &path);
        ~Texture();

        void Render();
};

#endif