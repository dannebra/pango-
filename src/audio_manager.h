#ifndef _AUDIO_MANAGER_H_
#define _AUDIO_MANAGER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>

class AudioManager
{
    private:
       Mix_Music *m_currentMusic = nullptr;
       bool Init();

    public:
        AudioManager()
        {
            Init();
        }
        
        ~AudioManager();
        AudioManager(const AudioManager &other) = delete;
        AudioManager(AudioManager &&other) = default;
        AudioManager& operator=(const AudioManager& other) = delete;
        AudioManager& operator=(AudioManager&& other) = delete;

        void LoadMusic(const std::string &path);
        void PlayMusic() const;
        void ToggleMusic() const;
};

#endif