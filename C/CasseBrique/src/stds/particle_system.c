#include "../../inc/stds/particle_system.h"

ParticleSystem_T* createParticleSystem(const int max_particles) {
    ParticleSystem_T* ps = malloc(sizeof(ParticleSystem_T));

    if (ps == NULL) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Error: could not allocate memory for ParticleSystem_T struct: %s.\n",
                    SDL_GetError());
        exit(15);
    }

    memset(ps, 0, sizeof(ParticleSystem_T));

    ps->particles = malloc(sizeof(Particle_T) * max_particles);
    ps->maxParticles = max_particles;
    ps->aliveCount = 0;
    ps->deadIndex = 0;

    return ps;
}

int insertParticle(ParticleSystem_T* ps, const Particle_T* p) {
    if (ps->aliveCount == ps->maxParticles - 1) {
        return PS_FULL;
    }

    if (!p->particleUpdate || !p->particleDraw) {
        return PS_INVALID_FP;
    }

    ps->particles[ps->aliveCount++] = *p;
    return PS_SUCCESS;
}

void updateParticleSystem(ParticleSystem_T* ps) {
    for (int i = 0; i < ps->aliveCount; i++) {
        Particle_T* p = &ps->particles[i];
        if (p->particleUpdate) {
            p->particleUpdate(p);
        }

        if (p->flags & DEATH_MASK) {
            ps->deadIndex = ps->aliveCount--;
            Particle_T* back_particle = &ps->particles[ps->deadIndex];

            const Particle_T tmp = *back_particle;
            *back_particle = *p;
            *p = tmp;
        }
    }
}

void drawParticleSystem(const ParticleSystem_T* ps) {
    for (int i = 0; i < ps->aliveCount; i++) {
        Particle_T* p = &ps->particles[i];
        if (p->particleDraw) {
            p->particleDraw(p);
        }
    }
}
