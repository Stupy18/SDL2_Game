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

    void setPos( float p_x, float p_y)
    {
        getPos().x=p_x;
        getPos().y=p_y;

    }
    
    SDL_Texture* get_Texture();
    SDL_Rect& get_currentFrame();

    std::vector<int> getCollisionPoints()
    {
        std::vector<int> points;
        points.push_back(getPos().x-15);
        points.push_back(getPos().x+get_currentFrame().w-50);
        points.push_back(getPos().y);
        points.push_back(getPos().y+get_currentFrame().h);
        return points;
    }

    void setY(float p_val)
    {
        pos.y=p_val;
    }
    void setX(float p_val)
    {
        pos.x=p_val;
    }

    void setFrameSize(int width, int height, int p_x, int p_y);

    int getWidth()
    {   
	return currentFrame.w;
    }

    int getHeight()
    {
	return currentFrame.h;
    }

    void setTexture(SDL_Texture* p_texture)
    {
        texture=p_texture;
    }

    SDL_Texture* getTexture()
    {
        return texture;
    }
    bool checkCollision(const SDL_Rect& otherRect) const;
};
