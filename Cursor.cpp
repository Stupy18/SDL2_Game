#include "Cursor.hpp"
#include "RenderWindow.hpp"

Cursor::Cursor(Vector2f p_pos, SDL_Texture* p_texture) 
    : Entity(p_pos, p_texture) {
    // You can set the cursor size here if different from the default Entity size
    setFrameSize(10, 10, 0, 0); // Width, Height, Texture X, Texture Y
}

void Cursor::update() {
    int x, y;
    SDL_GetMouseState(&x, &y);

    // Update cursor position directly without scaling
    setX(x);
    setY(y);
}

