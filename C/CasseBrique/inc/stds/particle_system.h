#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "stds.h"

enum { PS_SUCCESS, PS_FULL, PS_INVALID_FP };

extern ParticleSystem_T* createParticleSystem(int32_t max_particles);

extern int insertParticle(ParticleSystem_T* ps, const Particle_T* p);

extern void updateParticleSystem(ParticleSystem_T* ps);

extern void drawParticleSystem(const ParticleSystem_T* ps);

#endif
