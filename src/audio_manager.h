#ifndef _AUDIO_MANAGER_H_
#define _AUDIO_MANAGER_H_

#include "asset_manager.h"

class AudioManager
{
    private:
        static AudioManager *s_Instance;
        AssetManager *m_AssetManager;

    public:
        static AudioManager *Instance();
        AudioManager(const AudioManager &other) = delete;
        AudioManager(AudioManager &&other) = default;
        AudioManager& operator=(const AudioManager& other) = delete;
        AudioManager& operator=(AudioManager&& other) = delete;

        static void FreeResources();
        void PlayMusic(const std::string &filename, int loops = -1) const; // -1 = loop forever
        void PlaySfx(const std::string &filename, int channel = 0, int loops = 0) const;
        void PauseMusic() const;
        void ResumeMusic() const;

    private:
        AudioManager();
        ~AudioManager();
};

#endif