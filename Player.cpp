 #include "Player.hpp"
#include <vector>
#include <iostream>

Player::Player(Vector2f p_pos, const std::vector<SDL_Texture*>& tex, float p_speed, int screenWidth, int screenHeight, Inventory spellInventory)
    : Entity(p_pos, tex[0]), 
      tex(tex), 
      speed(p_speed), 
      movingUp(false), 
      movingDown(false), 
      movingLeft(false), 
      movingRight(false),
      isJumping(false), 
      jumpSpeed(6), 
      originalYPos(p_pos.y), 
      currentJumpHeight(0.0f),
      screenWidth(screenWidth), 
      screenHeight(screenHeight), 
      gravitySpeed(4.0f), 
      damage(1.0f), 
      health(100), 
      currentAmmo(6), 
      totalAmmo(99), 
      isEmpty(false), 
      spellInventory(spellInventory) // Use the member variable name here
{
    // Constructor body (if needed)
}


void Player::handleInput(SDL_Event &event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_SPACE: 
                if (!isJumping && onGround) {
                    // First jump
                    isJumping = true;
                    canDoubleJump = true; // Reset double jump for when player is in the air
                    currentJumpHeight = 0.0f;
                } else if (!isJumping && canDoubleJump) {
                    // Double jump
                    isJumping = true;
                    canDoubleJump = false; // Double jump used
                    currentJumpHeight = 0.0f;
                }
                break;
            case SDLK_s:
             {
             movingDown = true;
             break;
            }
            case SDLK_a: movingLeft = true; setTexture(tex[1]); break;
            case SDLK_d:{

             movingRight = true; 
             setTexture(tex[0]);
             break;
            }
            case SDLK_1: {
                Spell& spell = getInventory().getItem_with_position(1);
                if (spell.canUseSpell()) {
                    spell.useSpell(currentTime);
                }
                break;
            }
            case SDLK_2:{

             getInventory().getItem_with_position(1).set_used();
            break;
            }
            case SDLK_3:{

             getInventory().getItem_with_position(3).set_used();
            break;
            }
            case SDLK_4:{

             getInventory().getItem_with_position(4).set_used();
            break;
            }
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
    reset();
    Vector2f& pos = getPos();
    SDL_Rect playerRect = {int(pos.x), int(pos.y), get_currentFrame().w, get_currentFrame().h};

    // Apply gravity
    if (!isJumping || (isJumping && currentJumpHeight >= get_currentFrame().h*2)) {
        pos.y += gravitySpeed; // Apply gravity
    }

    // Handle horizontal movement
    if (movingLeft) pos.x -= speed;
    if (movingRight) pos.x += speed;

    // Handle jumping
    if (isJumping && currentJumpHeight < get_currentFrame().h*2) {
        pos.y -= jumpSpeed; // Move up during jump
        currentJumpHeight += jumpSpeed;
    } else if (currentJumpHeight >= get_currentFrame().h*2) {
        isJumping = false; // End the jump
    }

    // Update playerRect for collision detection
    playerRect.y = int(pos.y);

    // Check for collisions with entities
    if (checkCollision(otherEntities)) {
        // Player is over an entity. Adjust position if colliding and reset jump
        onGround = true;
        isJumping = false;
        currentJumpHeight = 0.0f;  // Reset double jump when landing on a platform
    } else {
        onGround = false; // Player is in the air
        gravitySpeed = 4.0f;
    }

    // Clamp horizontal position
    pos.x = clamp(pos.x, 0, screenWidth);
    // pos.y = clamp(pos.y, 0, screenHeight+200);
}





void Player::render(SDL_Renderer* renderer) {
    SDL_Rect srcRect = get_currentFrame();
    const Vector2f& pos = getPos();  // Get a reference to the position
    SDL_Rect dstRect = { (int)pos.x, (int)pos.y, srcRect.w, srcRect.h};
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
    SDL_Rect playerRect = {int(getPos().x), int(getPos().y), get_currentFrame().w, get_currentFrame().h};

    for (Entity& entity : entityVector) {
        std::vector<int> collisionPoints = entity.getCollisionPoints();
        SDL_Rect entityRect = {collisionPoints.at(0), collisionPoints.at(2), collisionPoints.at(1) - collisionPoints.at(0), collisionPoints.at(3) - collisionPoints.at(2)};

        if (playerRect.x < entityRect.x + entityRect.w &&
            playerRect.x  + playerRect.w > entityRect.x &&
            playerRect.y < entityRect.y + entityRect.h &&
            playerRect.y + playerRect.h > entityRect.y) {
            
            handleCollision(playerRect, entityRect);
            return true;
        }
    }
    return false;
}

void Player::handleCollision(const SDL_Rect& playerRect, const SDL_Rect& entityRect) {
    // Calculate overlap on both X and Y axes
    int overlapX = std::min(playerRect.x + playerRect.w, entityRect.x + entityRect.w) - std::max(playerRect.x, entityRect.x);
    int overlapY = std::min(playerRect.y + playerRect.h, entityRect.y + entityRect.h) - std::max(playerRect.y, entityRect.y);

    // Determine the side of the collision based on the least amount of overlap
    if (overlapX + 2 > overlapY) { // Collision is vertical
        if (playerRect.y + playerRect.h - overlapY == entityRect.y) {
            // Collision on the top
            setY(entityRect.y - playerRect.h + 1);
            onGround = true;
            isJumping = false;
            canDoubleJump = true; // Reset jump and double jump
            gravitySpeed = 0; // Stop applying gravity when on ground
        } else {
            // Collision on the bottom
            setY(entityRect.y + entityRect.h);
            gravitySpeed = 0.90f; // Apply gravity if not on ground
        }
    } else { // Collision is horizontal
        if (playerRect.x + playerRect.w - overlapX == entityRect.x) {
            // Collision on the left
            setX(entityRect.x - playerRect.w );
        } else {
            // Collision on the right
            setX(entityRect.x + entityRect.w );
            setY(getPos().y);
        }
    }
}

void Player::reset()
{
    if (getPos().y>=screenHeight+300) {

    setX(100);
	setY(700);
    health=health - 25;
    }
}

void Player::reload()
{
    totalAmmo=totalAmmo - 6 + currentAmmo;
    currentAmmo=6;
    isEmpty=false;
}

void Player::startReloading() {
        isReloading = true;
        reloadTimer = 2.0f;  // Set the reload duration to 2 seconds
    }

void Player::updateReloadTimer(float deltaTime) {
        if (isReloading) {
            reloadTimer -= deltaTime;
            if (reloadTimer <= 0) {
                isReloading = false;
                reload();  // Reload the ammo here
            }
        }
    }
bool Player::isCurrentlyReloading() const {
        return isReloading;
    }