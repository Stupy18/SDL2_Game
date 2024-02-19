#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entity.hpp"
#include "Background.hpp"

class RenderWindow 
{
public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	void cleanUp();
	SDL_Texture* loadTexture(const char* p_filePath);
	void clear();
	void render(Entity& p_entity);
	void renderBackground(Background& p_entity);
	void display();
	int getRefreshRate();
	SDL_Renderer* getRenderer()
	{
		return renderer;
	}
	SDL_Window* getWindow()
	{
		return window;
	}

	void applyFadeEffect(SDL_Renderer* renderer, int startAlpha, int endAlpha, int duration);

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	};