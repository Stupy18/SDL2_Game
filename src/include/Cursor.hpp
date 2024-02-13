#pragma once
#include "Entity.hpp"

class Cursor : public Entity {
public:
    Cursor(Vector2f p_pos, SDL_Texture* p_texture);

    void update();  // Override the update method to set the cursor's position
    void render(SDL_Renderer* renderer); // Render the cursor
};
