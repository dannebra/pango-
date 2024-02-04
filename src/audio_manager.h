#ifndef _AUDIO_MANAGER_H_
#define _AUDIO_MANAGER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>

class AudioManager
{
    private:
        static AudioManager *s_Instance;
        Mix_Music *m_currentMusic = nullptr;
        bool m_Initialized = false;

    public:
        static AudioManager *Instance();
        AudioManager(const AudioManager &other) = delete;
        AudioManager(AudioManager &&other) = default;
        AudioManager& operator=(const AudioManager& other) = delete;
        AudioManager& operator=(AudioManager&& other) = delete;

        bool HasInitialized();
        void FreeResources();
        void LoadMusic(const std::string &path);
        void PlayMusic() const;
        void ToggleMusic() const;

    private:
        AudioManager();
        ~AudioManager();
};

#endif