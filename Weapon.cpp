// Weapon.cpp
#include "Weapon.hpp"
#include <math.h>

// Constructor implementation
Weapon::Weapon(SDL_Texture* p_texture)
    : Entity(Vector2f(0, 0), p_texture) {
    setFrameSize(140, 140, 0, 0); // Example frame size, adjust as needed
}

// Member function to update the weapon's position relative to the player
void Weapon::updatePositionAndRotation(const Vector2f& playerPosition, const Vector2f& cursorPosition, Player& player) {
    float angle = calculateAngle(playerPosition, cursorPosition);

    // Determine the flip state based on the angle
    bool shouldFlip = angle > 90 || angle < -90;
    if (player.isStandingStill())
        {
            player.setFacingRight();
        }

    // Correct the angle for rendering when flipped
    if (shouldFlip) {
        angle = angle + ((angle > 0) ? -180 : 180);
        if (player.isStandingStill())
        {
            player.setFacingLeft();
        }
    }

    // Calculate dynamic offset based on angle
    float radians = angle * (M_PI / 180);
    Vector2f offset;

    if (!shouldFlip) 
        {
            // Offset when facing right (adjust as necessary for your sprite)
            offset.x = cos(radians) * 20 - 35; // The weapon extends to the right
            offset.y = sin(radians) * 20 -2; // The weapon raises or lowers with the cursor
        } 
    else 
        {
            // Offset when facing left (adjust as necessary for your sprite)
            // Flip the cosine component for left-facing offset
            offset.x = cos(M_PI - radians) * 20 + 15 ; // The weapon extends to the left, ensure this works with your sprite
            offset.y = -sin(M_PI - radians) * 20 - 2; // The weapon raises or lowers with the cursor
            // Additional adjustments may be necessary here to match your sprite's anchor point
        }
    // Apply calculated position
    setPos(playerPosition.x + offset.x, playerPosition.y + offset.y);

    setRotation(angle);
    setFlip(shouldFlip);
}



float Weapon::calculateAngle(const Vector2f& from, const Vector2f& to) {
    float deltaY = to.y - from.y;
    float deltaX = to.x - from.x;
    float angle = atan2(deltaY, deltaX) * (180.0 / M_PI); // Convert radians to degrees
    return angle;
}
