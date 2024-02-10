// Background.cpp
#include "Background.hpp"

Background::Background(SDL_Texture* p_texture, int screenWidth, int screenHeight)
    : Entity(Vector2f(0,0), p_texture) {
        SDL_Rect& frame = get_currentFrame();
        frame.w = screenWidth;
        frame.h = screenHeight;
}