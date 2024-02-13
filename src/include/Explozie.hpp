#pragma once
#include <iostream>
#include "Entity.hpp"

struct Explosion {
    Entity entity;
    float startTime;
    float duration;
    std::vector<SDL_Texture*> textures; // Textures for different animation stages
    int currentStage;

    Explosion(Entity e, float start, float dur, const std::vector<SDL_Texture*>& tex)
        : entity(e), startTime(start), duration(dur), textures(tex), currentStage(0) {}

    void update(float currentTime) {
        float timeElapsed = currentTime - startTime;
        currentStage = static_cast<int>(timeElapsed / 0.1f); // Change stage every 0.2 seconds
        if (currentStage < textures.size()) {
            entity.setTexture(textures[currentStage]);
        }
    }

    bool isFinished(float currentTime) {
        return currentTime - startTime > duration;
    }
};

