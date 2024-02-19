#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Background.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetLogicalSize(renderer, 1920, 1080);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath) 
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);

    if (texture == NULL)
        std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
    return texture;
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity)
{
    SDL_Rect src;
    src.x = p_entity.get_currentFrame().x;
    src.y = p_entity.get_currentFrame().y;
    src.w = p_entity.get_currentFrame().w;
    src.h = p_entity.get_currentFrame().h;

    SDL_Rect destination;
    destination.x = p_entity.getPos().x;
    destination.y = p_entity.getPos().y;
    destination.w = p_entity.get_currentFrame().w;
    destination.h = p_entity.get_currentFrame().h;

    SDL_RenderCopy(renderer, p_entity.get_Texture(), &src, &destination);
}

void RenderWindow::renderBackground(Background& p_entity)
{
    SDL_Rect src;
    src.x = p_entity.get_currentFrame().x;
    src.y = p_entity.get_currentFrame().y;
    src.w = p_entity.get_currentFrame().w;
    src.h = p_entity.get_currentFrame().h;

    SDL_Rect destination;
    destination.x = p_entity.getPos().x;
    destination.y = p_entity.getPos().y;
    destination.w = p_entity.get_currentFrame().w;
    destination.h = p_entity.get_currentFrame().h;

    SDL_RenderCopy(renderer, p_entity.get_Texture(), &src, &destination);
}

void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}

int RenderWindow::getRefreshRate()
{
    int displayIndex = SDL_GetWindowDisplayIndex(window);

    SDL_DisplayMode mode;
    SDL_GetDisplayMode(displayIndex, 0, &mode);

    return mode.refresh_rate;
}

void RenderWindow::applyFadeEffect(SDL_Renderer* renderer, int startAlpha, int endAlpha, int duration) {
    int alpha = startAlpha;
    int alphaStep = abs((endAlpha - startAlpha)) / duration;

    for (int i = 0; i < duration; ++i) {
        alpha += alphaStep;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, alpha);
        SDL_RenderFillRect(renderer, NULL);
        SDL_RenderPresent(renderer);
        SDL_Delay(8); // Delay to control the speed of the fade
    }
}
