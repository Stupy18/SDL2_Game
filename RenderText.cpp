#include "RenderText.hpp"
#include <iostream>

RenderText::RenderText(SDL_Renderer* renderer, const std::string& fontPath, int fontSize) {
    // Initialize TTF library
    TTF_Init();

    // Load the font
    font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (font == nullptr) {
        std::cout<< "Teapa" << std::endl;
    }

    this->renderer = renderer;
}

RenderText::~RenderText() {
    if (font != nullptr) {
        TTF_CloseFont(font);
    }

    TTF_Quit();
}

void RenderText::display(const std::string& text, int x, int y, SDL_Color color) {
    // Create surface from the text
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (surface == nullptr) {
        std::cout << "Surface creation failed: " << TTF_GetError() << std::endl;
        return;
    }

    // Create texture from surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
        std::cout << "Texture creation failed: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return;
    }

    // Copy the texture to the renderer
    SDL_Rect textRect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, nullptr, &textRect);

    // Clean up
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
