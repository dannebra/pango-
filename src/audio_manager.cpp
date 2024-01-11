#include "audio_manager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>

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
void AudioManager::PlayMusic()
{
    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(m_currentMusic, -1);
    }
}


void AudioManager::ToggleMusic()
{
    if (Mix_PausedMusic() == 1) {
        Mix_ResumeMusic();
    } else {
        Mix_PauseMusic();
    }
}

AudioManager::~AudioManager()
{
    Mix_FreeMusic(m_currentMusic);
}
