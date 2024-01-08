#include "../../inc/stds/sound.h"

static void loadSounds(void);

static Mix_Chunk* sounds[SND_MAX];
static Mix_Music* music;

void initSounds(void) {
    memset(sounds, 0, sizeof(Mix_Chunk *) * SND_MAX);

    music = NULL;

    loadSounds();
}

void loadMusic(const char* musicPath) {
    if (music != NULL) {
        Mix_HaltMusic();
        Mix_FreeMusic(music);
        music = NULL;
    }

    music = Mix_LoadMUS(musicPath);
}

void playMusic(const bool isPlaying) {
    Mix_PlayMusic(music, isPlaying ? -1 : 0);
}

void playSound(const int soundEffectId, const int channel) {
    Mix_PlayChannel(channel, sounds[soundEffectId], 0);
}

static void loadSounds(void) {
    sounds[SND_BRICK_SHATTER] = Mix_LoadWAV("res/sfx/hitblock.ogg");
    sounds[SND_BRICK_BREAK] = Mix_LoadWAV("res/sfx/blockbreak.ogg");
    sounds[SND_COIN] = Mix_LoadWAV("res/sfx/coin.ogg");
    sounds[SND_EXTRA_LIFE] = Mix_LoadWAV("res/sfx/extra-life.ogg");
}
