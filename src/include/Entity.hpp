#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Math.hpp"

class Entity
{
private:
    Vector2f pos;
    SDL_Rect currentFrame;
    SDL_Texture* texture;

public:
    Entity(Vector2f p_pos, SDL_Texture* p_texture);
    void init();
    
    Vector2f& getPos()
    {
        return pos;
    }
    SDL_Texture* get_Texture();
    SDL_Rect& get_currentFrame();

};
