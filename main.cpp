#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <vector>
using namespace std;

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"
#include "Background.hpp"
#include "Player.hpp"
#include "Cursor.hpp"

const int WIDTH = 1920, HEIGHT = 1080;

int main( int argc,char* args[]) {

    if (SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR " << SDL_GetError() << std::endl;

    }

    if (! IMG_Init(IMG_INIT_PNG))
        std::cout << "IMG_Init has failed. Error" << SDL_GetError() << std::endl;

    RenderWindow window("GAME v1.0",1920, 1080);
    SDL_SetWindowFullscreen(window.getWindow(), SDL_WINDOW_FULLSCREEN);
    int windowRefreshRate = window.getRefreshRate();

    SDL_Texture* grassTexture1 = window.loadTexture("src/res/images/groundTile.png");
    SDL_Texture* grassTexture2 = window.loadTexture("src/res/images/groundTile2.png");
    SDL_Texture* grassTexture3 = window.loadTexture("src/res/images/groundTile3.png");
    SDL_Texture* backgroundTexture = window.loadTexture("src/res/images/background.jpg");
    SDL_Texture* playerTexture = window.loadTexture("src/res/images/character3.png");
    SDL_Texture* cursorTexture = window.loadTexture("src/res/images/character3.png");

    Background background= Background(backgroundTexture, 1920,1080);
    Player player(Vector2f(100, 780), playerTexture, 2.5, WIDTH, HEIGHT);
    player.setFrameSize(64,64,0,0);
    Cursor cursor({0, 0}, cursorTexture);

    std::vector<Entity> entities = {
                            Entity(Vector2f(0,800),grassTexture1),
                            Entity(Vector2f(400,600),grassTexture1),
                            Entity(Vector2f(528,600),grassTexture1),
                            Entity(Vector2f(656,600),grassTexture1),
                            Entity(Vector2f(128,800),grassTexture3),
                            Entity(Vector2f(256,800),grassTexture3),
                            Entity(Vector2f(600,800),grassTexture2), 
                            Entity(Vector2f(728,800),grassTexture3), 
                            Entity(Vector2f(1000,800),grassTexture2),
                            Entity(Vector2f(1128,800),grassTexture1),
                            Entity(Vector2f(1256,800),grassTexture3),
                            Entity(Vector2f(1536,800),grassTexture2),
                            Entity(Vector2f(1664,800),grassTexture3),
                            Entity(Vector2f(1792,800),grassTexture3)

                            };

    entities.at(1).setFrameSize(128,32,0,0);
    entities.at(2).setFrameSize(128,32,0,0);
    entities.at(3).setFrameSize(128,32,0,0);

    bool gameRunning=true;
    SDL_Event event;
    const float timeStep = 0.01f;
    float accumulator = 0.0f;
    float currentTime = utils::hireTimeInSeconds();


    while (gameRunning)
    {
        int startTicks = SDL_GetTicks();
        float newTime = utils::hireTimeInSeconds();
        float frameTime = newTime - currentTime;
        
        currentTime = newTime;

        accumulator += frameTime;

        while(accumulator >= timeStep)
        {
            while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                gameRunning=false;

            player.handleInput(event);
        }

            accumulator -=timeStep;
        
        }

        const float alpha = accumulator / timeStep;
        window.clear();

        window.renderBackground(background);

        for (Entity& e : entities)
        {
            window.render(e);
            // Vector2f entityPos = e.getPos();
            // std:: cout << entityPos.x << std::endl;
            // std:: cout << entityPos.y << std::endl;
            // std:: cout << e.get_currentFrame().x << std::endl;
            // std:: cout << e.get_currentFrame().y << std::endl;
            // std:: cout << e.getCollisionPoints().at(0) << std::endl;
            // std:: cout << e.getCollisionPoints().at(1) << std::endl;
            // std:: cout << e.getCollisionPoints().at(2) << std::endl;
            // std:: cout << e.getCollisionPoints().at(3) << std::endl;
        }

        player.update(entities);
        SDL_Renderer* renderer = window.getRenderer();  // Get the renderer from your RenderWindow
        cursor.update();
        window.render(player);
        window.render(cursor);
        // std:: cout << player.get_onGround() << std::endl;

        

        window.display();

        int frameTicks = SDL_GetTicks() - startTicks;
        if(frameTicks < 1000 /window.getRefreshRate())
            SDL_Delay(1000 /window.getRefreshRate() - frameTicks);
    }
    window.cleanUp();
    SDL_Quit();
    return 0;

}