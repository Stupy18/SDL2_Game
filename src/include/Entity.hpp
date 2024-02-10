#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Math.hpp"
#include <vector>

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

    std::vector<int> getCollisionPoints()
    {
        std::vector<int> points;
        points.push_back(getPos().x);
        points.push_back(getPos().x+get_currentFrame().w);
        points.push_back(getPos().y);
        points.push_back(getPos().y+get_currentFrame().h);
        return points;
    }


};
