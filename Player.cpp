#include "Player.hpp"
#include <vector>
#include <iostream>

Player::Player(Vector2f p_pos, SDL_Texture* p_texture, int p_speed, int screenWidth, int screenHeight)
    : Entity(p_pos, p_texture), speed(p_speed), movingUp(false), movingDown(false), movingLeft(false), movingRight(false),
      isJumping(false), jumpSpeed(1.37f), originalYPos(p_pos.y), currentJumpHeight(0.0f),
      screenWidth(screenWidth), screenHeight(screenHeight), gravitySpeed(0.5f) {}

void Player::handleInput(SDL_Event &event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_SPACE: 
                if (!isJumping && onGround) {
                    isJumping = true;
                    currentJumpHeight = 0.0f;
                }
                break;
            case SDLK_s: movingDown = true; break;
            case SDLK_a: movingLeft = true; break;
            case SDLK_d: movingRight = true; break;
        }
    } else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_SPACE: 
                // No need to handle space key on key up for jumping
                break;
            case SDLK_s: movingDown = false; break;
            case SDLK_a: movingLeft = false; break;
            case SDLK_d: movingRight = false; break;
        }
    }
}



void Player::update(std::vector<Entity>& otherEntities) {
    Vector2f& pos = getPos();
    SDL_Rect playerRect = {int(pos.x), int(pos.y), get_currentFrame().w, get_currentFrame().h};

    // Apply gravity
    if (!isJumping || (isJumping && currentJumpHeight >= 40 && !get_onGround())) {
        pos.y += gravitySpeed; // Apply gravity
    }

    // Handle horizontal movement
    if (movingLeft) pos.x -= speed;
    if (movingRight) pos.x += speed;

    // Handle jumping
    if ((isJumping && currentJumpHeight < 40) || (!get_onGround() && currentJumpHeight < 40)) {
        pos.y -= jumpSpeed; // Move up during jump
        currentJumpHeight += jumpSpeed;
        onGround = false; // Player is in the air
    } else if (currentJumpHeight >= 40) {
        isJumping = false; // End the jump
    }

    // Update playerRect for collision detection
    playerRect.y = int(pos.y);

    // Check for collisions with entities
    if (checkCollision()) {
        pos.y = 107; // Adjust position if colliding
        onGround = true; // Player is on the ground or an entity
        isJumping = false;
        currentJumpHeight = 0.0f;
    } else {
        onGround = false; // Player is in the air
    }

    // Clamp horizontal position
    pos.x = clamp(pos.x, 0, 290);
    pos.y = clamp(pos.y, 0, 150);
}




void Player::render(SDL_Renderer* renderer) {
    SDL_Rect srcRect = get_currentFrame();
    const Vector2f& pos = getPos();  // Get a reference to the position
    SDL_Rect dstRect = { (int)pos.x, (int)pos.y, srcRect.w, srcRect.h };
    SDL_RenderCopy(renderer, get_Texture(), &srcRect, &dstRect);
}

float Player::clamp(float p_value, float p_min, float p_max)
{
	if (p_value > p_max)
		return p_max;
	if (p_value < p_min)
		return p_min;
	return p_value;
}

bool Player::checkCollision() {
    float playerX = getPos().x;
    float playerY = getPos().y;
    // for (Entity& entity : entityVector) {
    //     Vector2f entityPos = entity.getPos();
    //     if ( (playerX>= entityPos.x && playerY >= entityPos.y) || (playerX >= entityPos.x && playerY <= entityPos.y) || 
    //         (playerX <= entityPos.x && playerY >= entityPos.y) || (playerX <= entityPos.x && playerY <= entityPos.y) )
    //         return true;
    // }

    if (playerY >= 107)
        return true;
    return false; // No collisions detected
}