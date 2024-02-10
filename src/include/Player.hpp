#pragma once
#include "Entity.hpp"
#include <vector>

class Player : public Entity {
private:
    int speed;
    bool movingUp, movingDown, movingLeft, movingRight;
	int screenWidth, screenHeight;
    bool isJumping;
    bool onGround=true;
    float jumpSpeed;
    float originalYPos;
    float currentJumpHeight;
    float gravity; // Gravity affecting the player
    float groundY=107; // The y-coordinate of the ground or platform
    float gravitySpeed;

public:
    Player(Vector2f p_pos, SDL_Texture* p_texture, int p_speed, int screenWidth, int screenHeight);
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


    bool checkCollision();

    bool get_onGround()
    {
        return onGround;
    }


};
