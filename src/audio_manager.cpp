#include "audio_manager.h"

AudioManager *AudioManager::s_Instance = nullptr;

AudioManager *AudioManager::Instance()
{
    if (s_Instance == nullptr) {
        s_Instance = new AudioManager();
    }

    return s_Instance;
}

void AudioManager::FreeResources()
{
    delete s_Instance;
    s_Instance = nullptr;
}

AudioManager::AudioManager()
{
    m_AssetManager = AssetManager::Instance();

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0 ) {  // 44.1khz frequency, stereo
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    } 

    Mix_Volume(0, 32);
}

AudioManager::~AudioManager()
{
    m_AssetManager = nullptr;
    Mix_Quit();
}

void AudioManager::PlayMusic(const std::string &filename, int loops) const
{
    Mix_PlayMusic(m_AssetManager->GetMusic(filename), loops);
}

void AudioManager::PlaySfx(const std::string &filename, int channel, int loops) const
{
    Mix_PlayChannel(channel, m_AssetManager->GetSfx(filename), loops);
}

void AudioManager::PauseMusic() const
{
    if (Mix_PlayingMusic() != 0) {
        Mix_PauseMusic();
    }
}

void AudioManager::ResumeMusic() const
{
    if (Mix_PausedMusic() != 0) {
        Mix_ResumeMusic();
    }
}