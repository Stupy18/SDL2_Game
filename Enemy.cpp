#include "Enemy.hpp"
#include <cmath>

Enemy::Enemy(Vector2f p_pos, SDL_Texture* p_texture, float p_speed,int health)
    : Entity(p_pos, p_texture), speed(p_speed) {
    // Initialize velocity or other properties here if needed
}

void Enemy::update(const Vector2f& playerPos) {
    Vector2f direction = playerPos - getPos();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) {
        velocity.x = (direction.x / length) * speed;
        velocity.y = (direction.y / length) * speed;
    }

    // Move towards the player
    Vector2f& pos = getPos();
    pos.x += velocity.x;
    pos.y += velocity.y;

    // Ensure enemy's current frame is set correctly for rendering
    // setFrameSize(...);
}

bool Enemy::checkCollisionWithPlayer(const SDL_Rect& playerRect) {
    SDL_Rect enemyRect = {int(getPos().x), int(getPos().y), get_currentFrame().w, get_currentFrame().h};
    return SDL_HasIntersection(&playerRect, &enemyRect);
}

bool Enemy::isDead() {
    return health <= 0;
}

void Enemy::damage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}