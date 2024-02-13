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

