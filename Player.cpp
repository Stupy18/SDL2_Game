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
    if (!isJumping || (isJumping && currentJumpHeight >= 40)) {
        pos.y += gravitySpeed; // Apply gravity
    }

    // Handle horizontal movement
    if (movingLeft) pos.x -= speed;
    if (movingRight) pos.x += speed;

    // Handle jumping
    if (isJumping && currentJumpHeight < 40) {
        pos.y -= jumpSpeed; // Move up during jump
        currentJumpHeight += jumpSpeed;
    } else if (currentJumpHeight >= 40) {
        isJumping = false; // End the jump
    }

    // Update playerRect for collision detection
    playerRect.y = int(pos.y);

    // Check for collisions with entities
    if (checkCollision(otherEntities)) {
        // Player is over an entity. Adjust position if colliding and reset jump
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

bool Player::checkCollision(std::vector<Entity>& entityVector) {
    float playerX = getPos().x + get_currentFrame().w / 2; // Center x-coordinate of the player
    float playerY = getPos().y + get_currentFrame().h; // Bottom y-coordinate of the player

    for (Entity& entity : entityVector) {
        std::vector<int> collisionPoints = entity.getCollisionPoints();
        float entityLeft = collisionPoints.at(0);
        float entityRight = collisionPoints.at(1);
        float entityTop = collisionPoints.at(2);

        // Check if the player is between the left and right edges of the entity and above the top
        if (playerX > entityLeft && playerX < entityRight && playerY > entityTop) {
            return true; // Collision detected (the player is over the entity)
        }
    }
    return false; // No collisions detected
}
