#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class RenderText {
public:
    RenderText(SDL_Renderer* renderer, const std::string& fontPath, int fontSize);
    ~RenderText();

    void display(const std::string& text, int x, int y, SDL_Color color);

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
};

