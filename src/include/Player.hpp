#pragma once
#include "Entity.hpp"
#include "Inventory.hpp"
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
    int currentAmmo;
    int totalAmmo;
    bool isEmpty;
    bool isReloading;
    float reloadTimer;
    Inventory spellInventory;
    float currentTime = 0.0f;
    

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

        int get_currentAmmo()
    {
        return currentAmmo;
    }

    int get_totalAmmo()
    {
        return totalAmmo;
    }

    void set_currentAmmo(int p_ammo)
    {
        currentAmmo=p_ammo;
    }

     void set_totalAmmo(int p_ammo)
    {
        totalAmmo=p_ammo;
    }

    void is_ammoEmpty()
    {
        if (currentAmmo<=0)
        {
            isEmpty=true;
        }
    
    }

    bool hasAmmo()
    {
        return !isEmpty;
    }

    void reload();

    void startReloading();
    void updateReloadTimer(float deltaTime);
    bool isCurrentlyReloading() const;


void setSpeed(float p_speed) {
    speed = p_speed;
}

void setMovingUp(bool p_movingUp) {
    movingUp = p_movingUp;
}

void setMovingDown(bool p_movingDown) {
    movingDown = p_movingDown;
}

void setMovingLeft(bool p_movingLeft) {
    movingLeft = p_movingLeft;
}

void setMovingRight(bool p_movingRight) {
    movingRight = p_movingRight;
}

void setIsJumping(bool p_isJumping) {
    isJumping = p_isJumping;
}

void setJumpSpeed(float p_jumpSpeed) {
    jumpSpeed = p_jumpSpeed;
}

void setOriginalYPos(float p_originalYPos) {
    originalYPos = p_originalYPos;
}

void setCurrentJumpHeight(float p_currentJumpHeight) {
    currentJumpHeight = p_currentJumpHeight;
}

void setScreenWidth(int p_screenWidth) {
    screenWidth = p_screenWidth;
}

void setScreenHeight(int p_screenHeight) {
    screenHeight = p_screenHeight;
}

void setGravitySpeed(float p_gravitySpeed) {
    gravitySpeed = p_gravitySpeed;
}

void setIsEmpty(bool p_isEmpty) {
    isEmpty = p_isEmpty;
}

void reset_stats()
{
    setPos(100, 780); // Set starting position
    setSpeed(2.5); // Set speed
    setMovingUp(false);
    setMovingDown(false);
    setMovingLeft(false);
    setMovingRight(false);
    setIsJumping(false);
    setJumpSpeed(6);
    setOriginalYPos(780); // Assuming this is the Y position
    setCurrentJumpHeight(0.0f);
    setScreenWidth(1920);
    setScreenHeight(1080);
    setGravitySpeed(4.0f);
    set_Damage(1.0f);
    set_Health(100);
    set_currentAmmo(6);
    set_totalAmmo(99);
    setIsEmpty(false);
}

    void addItemToInventory(const Spell& spell) {
        spellInventory.addItem(spell);
    }

    void removeItemFromInventory(const std::string& spellName) {
        spellInventory.removeItem(spellName);
    }

    // You might also want methods to check the inventory, get items, etc.
    Inventory getInventory() const {
        return spellInventory;
    }

    void updateCurrentTime(float newTime) {
        currentTime = newTime;
    }
    
};
