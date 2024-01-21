#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <SDL2/SDL_image.h>
#include <string>

class Texture
{
    public:
        SDL_Texture *m_texture = nullptr;

        Texture() = delete;
        
        Texture(SDL_Renderer *renderer, const std::string &path)
        {
            m_texture = IMG_LoadTexture(renderer, path.c_str());
        }
        
        ~Texture()
        {
            SDL_DestroyTexture(m_texture);
            m_texture = nullptr;
        }
};

#endif