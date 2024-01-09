#ifndef _AUDIO_MANAGER_H_
#define _AUDIO_MANAGER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>

class AudioManager
{
    private:
       Mix_Music *m_currentMusic = nullptr;

    public:
        AudioManager() = default;
        ~AudioManager();

        void LoadMusic(const std::string &path);
        void PlayMusic();
        void ToggleMusic();
};

#endif