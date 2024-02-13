#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Bullet.hpp"
#include <cmath>

Bullet::Bullet(Vector2f p_pos, SDL_Texture* p_texture, Vector2f p_target, float p_speed)
    : Entity(p_pos, p_texture), speed(p_speed) {
    // Calculate direction towards the target (cursor position)
    Vector2f direction = p_target - p_pos;
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    velocity = Vector2f((direction.x / length) * speed, (direction.y / length) * speed);

    setFrameSize(33,33, 0, 0); // Set the bullet size, adjust as needed
}

void Bullet::update(float deltaTime) {
    Vector2f& pos = getPos();
    pos.x += velocity.x * deltaTime;
    pos.y += velocity.y * deltaTime;
}

bool Bullet::isOffScreen(int screenWidth, int screenHeight) {
    Vector2f& pos = getPos();
    return pos.x < 0 || pos.y < 0 || pos.x > screenWidth || pos.y > screenHeight;
}

bool Bullet::checkCollision(std::vector<Entity>& entityVector) {
    SDL_Rect playerRect = {int(getPos().x), int(getPos().y), get_currentFrame().w, get_currentFrame().h};

    for (Entity& entity : entityVector) {
        std::vector<int> collisionPoints = entity.getCollisionPoints();
        SDL_Rect entityRect = {collisionPoints.at(0), collisionPoints.at(2), collisionPoints.at(1) - collisionPoints.at(0), collisionPoints.at(3) - collisionPoints.at(2)};

        if (playerRect.x < entityRect.x + entityRect.w &&
            playerRect.x + playerRect.w > entityRect.x &&
            playerRect.y < entityRect.y + entityRect.h &&
            playerRect.y + playerRect.h > entityRect.y) {
            
            return true;
        }
    }
    return false;
}
