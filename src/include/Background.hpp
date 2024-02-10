#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Entity.hpp"

class Background : public Entity
{
public:
    // Constructor for the Background class
    Background(SDL_Texture* p_texture, int screenWidth, int screenHeight);

    // Optionally, you can declare more functions specific to the Background class here
};
