#include "audio_manager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>

AudioManager *AudioManager::s_Instance = nullptr;

AudioManager *AudioManager::Instance()
{
    if (s_Instance == nullptr) {
        s_Instance = new AudioManager();
    }

    return s_Instance;
}

/**
 * Load the music that will be played. Overwrites the currently selected music.
 * @param path path to the audio file in mp3 format 
*/
void AudioManager::LoadMusic(const std::string &path)
{
    Mix_FreeMusic(m_currentMusic);
    Mix_Music *music = Mix_LoadMUS(path.c_str());
    if (music == NULL) {
        printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
    } else {
        m_currentMusic = music;
    }
}

/**
 * Play the most recently loaded music.
 * If no music has been loaded then this function does nothing.
*/
void AudioManager::PlayMusic() const
{
    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(m_currentMusic, -1);
    }
}

void AudioManager::ToggleMusic() const
{
    if (Mix_PausedMusic() == 1) {
        Mix_ResumeMusic();
    } else {
        Mix_PauseMusic();
    }
}

void AudioManager::FreeResources()
{
    Mix_FreeMusic(m_currentMusic);
    m_currentMusic = nullptr;
    Mix_Quit();
}

AudioManager::AudioManager()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0 ) {  // 44khz frequency, stereo
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        m_Initialized = false;
    } else {
        m_Initialized = true;
    }
}


AudioManager::~AudioManager()
{
    FreeResources();
}
