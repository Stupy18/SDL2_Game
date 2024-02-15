#pragma once
#include "Entity.hpp"
#include "Math.hpp"

class Enemy : public Entity {
private:
    Vector2f velocity;
    float speed;
    int health;
    bool markedForRemoval;

public:
    Enemy(Vector2f p_pos, SDL_Texture* p_texture, float p_speed,int p_health);
    void update(const Vector2f& playerPos); // Update enemy's position to follow the player
    bool checkCollisionWithPlayer(const SDL_Rect& playerRect);
    bool isDead();
    int getHealth()
    {
        return health;
    }
    void setHealth(int p_health)
    {
        health=p_health;
    }

    void takeDamage(int damageAmount);

    bool isMarkedForRemoval() const {
        return markedForRemoval;
    }

    void markForRemoval() {
        markedForRemoval = true;
    }

};
