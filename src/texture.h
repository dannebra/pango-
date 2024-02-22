#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "game_entity.h"
#include "graphics.h"
#include <SDL2/SDL_image.h>
#include <string>

class Texture : public GameEntity
{
    protected:
        SDL_Texture *m_Texture;
        Graphics *m_Graphics;

        int m_Width{};
        int m_Height{};
        bool m_Clipped;
        SDL_Rect m_RenderRect;
        SDL_Rect m_ClippedRect;
    public:
        Texture() = delete;
        Texture(const std::string &filename);
        Texture(const std::string &filename, int x, int y, int width, int height);
        Texture(const std::string &text, const std::string &fontPath, const int size, const SDL_Color color);
        ~Texture();

        virtual void Render() override;
    private:
        void Setup(const std::string &filename);
};

#endif