#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entity.hpp"
#include "Math.hpp"

class Bullet : public Entity {
private:
    Vector2f velocity;
    float speed;

public:
    Bullet(Vector2f p_pos, SDL_Texture* p_texture, Vector2f p_target, float p_speed);

    void update(float deltaTime);  // Override the update method to move the bullet
    bool isOffScreen(int screenWidth, int screenHeight);
    bool checkCollision(std::vector<Entity>& entityVector);
};
