#pragma once
#include <SDL2/SDL.h>

namespace utils
{
    float hireTimeInSeconds()
    {
        float t = SDL_GetTicks();
        t *= 0.001f;
        
        return t;
    }

    Vector2f getRandomSpawnPositionOutsideScreen(int screenWidth, int screenHeight)
    {
    int randomx = (rand() % 1920);
    int randomy =  -50 -  (rand() % 300);
    return Vector2f(randomx,randomy);

    }

    float easeOutQuad(float t) {
    return t * (2 - t);
    }

    struct Transition {
    float duration;
    float elapsed;
    int startAlpha;
    int endAlpha;
    bool active;

    Transition() : duration(0), elapsed(0), startAlpha(0), endAlpha(0), active(false) {}

    void start(int startAlpha, int endAlpha, float duration) {
        this->startAlpha = startAlpha;
        this->endAlpha = endAlpha;
        this->duration = duration;
        this->elapsed = 0;
        this->active = true;
    }

    bool update(float deltaTime) {
        if (!active) return false;

        elapsed += deltaTime;
        if (elapsed >= duration) {
            active = false;
            elapsed = duration;
        }
        return true;
    }

    int getCurrentAlpha() const {
        float progress = elapsed / duration;
        return static_cast<int>(startAlpha + (endAlpha - startAlpha) * progress);
    }
};

}