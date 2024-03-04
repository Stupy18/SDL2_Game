// Weapon.cpp
#include "Weapon.hpp"
#include <math.h>

// Constructor implementation
Weapon::Weapon(SDL_Texture* p_texture)
    : Entity(Vector2f(0, 0), p_texture) {
    setFrameSize(150, 150, 0, 0); // Example frame size, adjust as needed
}

// Member function to update the weapon's position relative to the player
void Weapon::updatePositionAndRotation(const Vector2f& playerPosition, const Vector2f& cursorPosition) {
    // Calculate angle
    float angle = calculateAngle(playerPosition, cursorPosition);

    // Determine the facing direction
    bool facingRight = angle < 90 && angle > -90;

    // Calculate the weapon's position
    // Adjust these values as necessary
    Vector2f offset = facingRight ? Vector2f(20, -10) : Vector2f(-20, -10);
    setPos(playerPosition.x + offset.x, playerPosition.y + offset.y);

    // Set the rotation of the weapon based on the calculated angle
    setRotation(angle);
}

float Weapon::calculateAngle(const Vector2f& from, const Vector2f& to) {
    float deltaY = to.y - from.y;
    float deltaX = to.x - from.x;
    float angle = atan2(deltaY, deltaX) * (180.0 / M_PI); // Convert radians to degrees
    return angle;
}
