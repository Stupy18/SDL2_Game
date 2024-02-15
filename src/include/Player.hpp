#pragma once
#include "Entity.hpp"
#include <vector>

class Player : public Entity {
private:
    float speed;
    bool movingUp, movingDown, movingLeft, movingRight;
	int screenWidth, screenHeight;
    bool isJumping;
    bool onGround=true;
    float jumpSpeed;
    float originalYPos;
    float currentJumpHeight;
    bool canDoubleJump=false;
    float gravity; // Gravity affecting the player
    float groundY=107; // The y-coordinate of the ground or platform
    float gravitySpeed;
    const std::vector<SDL_Texture*>& tex;
    float damage;
    int health;

public:
    Player(Vector2f p_pos, const std::vector<SDL_Texture*>& tex, float p_speed, int screenWidth, int screenHeight);
    void handleInput(SDL_Event &event);  // Handle keyboard input
    void update(std::vector<Entity>& otherEntities);                       // Update player's position based on input and collision
    void render(SDL_Renderer* renderer); // Render the player
	int get_screenWidth(){
        return screenWidth;
    }
    int get_screenHeight(){
        return screenHeight;
    }

    float clamp(float p_value, float p_min, float p_max);


    bool checkCollision(std::vector<Entity>& entityVector);

    bool get_onGround()
    {
        return onGround;
    }
    void handleCollision(const SDL_Rect& playerRect, const SDL_Rect& entityRect);

    void reset();

    float get_Damage()
    {
        return damage;
    }

    void set_Damage(float p_damage)
    {
        damage=p_damage;
    }

    int get_Health()
    {
        return health;
    }

    void set_Health(int p_health)
    {
        health=p_health;
    }


};
