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
}