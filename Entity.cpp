#include "Entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Entity::Entity(Vector2f p_pos ,SDL_Texture* p_texture)
{
    pos = p_pos;
    texture=p_texture;
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 128;
    currentFrame.h = 128;
}

SDL_Texture* Entity::get_Texture()
{
    return texture;
}

SDL_Rect& Entity::get_currentFrame() {
    return currentFrame;
}

void Entity::setFrameSize(int width, int height, int p_x, int p_y) {
    currentFrame.w = width;
    currentFrame.h = height;
    currentFrame.x = p_x;
    currentFrame.y = p_y;
}
bool Entity::checkCollision(const SDL_Rect& otherRect) const {
    SDL_Rect thisRect = {int(pos.x), int(pos.y), currentFrame.w, currentFrame.h};

    // Check if any of the sides from thisRect are outside of otherRect
    if (thisRect.x + thisRect.w <= otherRect.x ||     // thisRect right edge past otherRect left
        thisRect.x >= otherRect.x + otherRect.w ||    // thisRect left edge past otherRect right
        thisRect.y + thisRect.h >= otherRect.y ||     // thisRect bottom edge past otherRect top
        thisRect.y <= otherRect.y + otherRect.h) {    // thisRect top edge past otherRect bottom
        return false; // No collision
    }

    return true; // Collision
}

float Entity::getRotation() const {
    return rotation;
}

void Entity::setRotation(float newRotation) {
    rotation = newRotation;
}

// Implement the setFlip method
void Entity::setFlip(bool shouldFlip) {
    flipped = shouldFlip;
}

// Implement the isFlipped method
bool Entity::isFlipped() const {
    return flipped;
}
