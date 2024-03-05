// Weapon.hpp
#pragma once
#include "Entity.hpp"
#include "Player.hpp"
#include <SDL2/SDL.h>

class Weapon : public Entity {
private:
    float angle; // Angle of the weapon relative to the player
public:
    // Constructor declaration
    Weapon(SDL_Texture* p_texture);

    // Member function to update the weapon's position relative to the player
    void updatePositionAndRotation(const Vector2f& playerPosition, const Vector2f& cursorPositionl,Player& player);
    float calculateAngle(const Vector2f& from, const Vector2f& to);
};
