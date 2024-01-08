#ifndef SOUND_H
#define SOUND_H

#include "stds.h"

extern void initSounds(void);

extern void loadMusic(const char* musicPath);

extern void playMusic(bool isPlaying);

extern void playSound(int soundEffectId, int channel);

#endif
