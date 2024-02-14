#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <vector>
#include <algorithm>
using namespace std;

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"
#include "Background.hpp"
#include "Player.hpp"
#include "Cursor.hpp"
#include "Bullet.hpp"
#include "../../../../../MinGW/lib/gcc/mingw32/6.3.0/include/c++/bits/algorithmfwd.h"
#include "Explozie.hpp"
#include "Enemy.hpp"

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
    int spawnInterval = 5; // Time in seconds between each enemy spawn
    float spawnTimer = spawnInterval; // Timer starts at the interval

    SDL_Texture* grassTexture1 = window.loadTexture("src/res/images/groundTile.png");
    SDL_Texture* grassTexture2 = window.loadTexture("src/res/images/groundTile2.png");
    SDL_Texture* grassTexture3 = window.loadTexture("src/res/images/groundTile3.png");
    SDL_Texture* backgroundTexture = window.loadTexture("src/res/images/background.jpg");
    SDL_Texture* playerTexture_left = window.loadTexture("src/res/images/character_stanga.png");
    SDL_Texture* playerTexture_right = window.loadTexture("src/res/images/character_dreapta.png");
    std::vector<SDL_Texture*> playerTextures = {playerTexture_right,playerTexture_left};
    SDL_Texture* cursorTexture = window.loadTexture("src/res/images/cursor.png");
    SDL_Texture* bulletTexture = window.loadTexture("src/res/images/bullet.png");
    SDL_Texture* explozieTexture1 = window.loadTexture("src/res/images/explozie.png");
    SDL_Texture* explozieTexture2 = window.loadTexture("src/res/images/explozie2.png");
    SDL_Texture* explozieTexture3 = window.loadTexture("src/res/images/explozie3.png");
    SDL_Texture* enemyTexture = window.loadTexture("src/res/images/explozie3.png");

    Background background= Background(backgroundTexture, 1920,1080);
    Player player(Vector2f(100, 780), playerTextures, 2.5, WIDTH, HEIGHT);
    player.setFrameSize(80,80,0,0);
    SDL_ShowCursor(SDL_DISABLE);
    Cursor cursor({0, 0}, cursorTexture);
    cursor.setFrameSize(62,62,0,0);
    std::vector<Bullet> bullets;
    std::vector<Explosion> explosions;
    std::vector<SDL_Texture*> explosionTextures = { explozieTexture1, explozieTexture2, explozieTexture3 };
    std::vector<Enemy> enemies;


    std::vector<Entity> entities = {
                            Entity(Vector2f(0,800),grassTexture1),
                            // Entity(Vector2f(400,600),grassTexture1),
                            // Entity(Vector2f(528,600),grassTexture1),
                            // Entity(Vector2f(656,600),grassTexture1),
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

    // entities.at(1).setFrameSize(128,32,0,0);
    // entities.at(2).setFrameSize(128,32,0,0);
    // entities.at(3).setFrameSize(128,32,0,0);

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

            // Check for mouse click to spawn a bullet
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                Vector2f cursorPos = cursor.getPos();
                Vector2f playerPos = player.getPos();
                bullets.emplace_back(playerPos, bulletTexture, cursorPos, 700.0f);
            }
        }

        accumulator -= timeStep;
    }

    const float alpha = accumulator / timeStep;
    window.clear();

    window.renderBackground(background);

    spawnTimer -= frameTime;

    // Check if it's time to spawn a new enemy
    if (spawnTimer <= 0) {
        // Reset the spawn timer
        spawnTimer = spawnInterval;
        
        // Spawn a new enemy
        Vector2f enemySpawnPos = utils::getRandomSpawnPositionOutsideScreen(WIDTH, HEIGHT);
        enemies.emplace_back(enemySpawnPos, enemyTexture, 1.3f);
    }

    for (Enemy& enemy : enemies) {
        enemy.update(player.getPos());
        window.render(enemy);
    }

    SDL_Rect playerRect = {int(player.getPos().x), int(player.getPos().y), player.get_currentFrame().w, player.get_currentFrame().h};

    for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();) {
        SDL_Rect enemyRect = {
            static_cast<int>(enemyIt->getPos().x),
            static_cast<int>(enemyIt->getPos().y),
            enemyIt->get_currentFrame().w,
            enemyIt->get_currentFrame().h
        };

        // Check collision with player
        if (SDL_HasIntersection(&playerRect, &enemyRect)) {
            // Remove the enemy on collision with the player
            enemyIt = enemies.erase(enemyIt);
            continue; // Skip the rest of the loop and proceed with the next iteration
        }

        bool enemyRemoved = false;
        for (auto bulletIt = bullets.begin(); bulletIt != bullets.end() && !enemyRemoved;) {
            SDL_Rect bulletRect = {
                static_cast<int>(bulletIt->getPos().x),
                static_cast<int>(bulletIt->getPos().y),
                bulletIt->get_currentFrame().w,
                bulletIt->get_currentFrame().h
            };

            if (SDL_HasIntersection(&enemyRect, &bulletRect)) {
                // Spawn explosion at bullet's position
                float bulletX=bulletIt->getPos().x;
                float bulletY=bulletIt->getPos().y;
                bulletIt->setPos(bulletX-50.0f,bulletY-50.0f);

                Entity explosionEntity = Entity(bulletIt->getPos(), explosionTextures[0]);
                explosions.emplace_back(explosionEntity, currentTime, 0.15f, explosionTextures);

                // Remove the bullet
                bulletIt = bullets.erase(bulletIt);

                // Remove the enemy
                enemyIt = enemies.erase(enemyIt);
                enemyRemoved = true; // Mark that the enemy was removed
            } else {
                ++bulletIt; // No collision, move to the next bullet
            }
        }

        if (!enemyRemoved) {
            ++enemyIt; // No bullets hit this enemy, move to the next enemy
        }
        // The enemyIt iterator is already correctly positioned for the next loop iteration
    }




    for (Entity& e : entities)
    {
        window.render(e);
    }


    player.update(entities);
    cursor.update();

    // Update bullets
    for (auto& bullet : bullets) {
        bullet.update(timeStep);
    }

    // Remove bullets that are off-screen
    // Iterate through the bullets in reverse order to avoid index issues while erasing
    for (int i = bullets.size() - 1; i >= 0; --i) {
        if (bullets[i].isOffScreen(WIDTH, HEIGHT)) {
            // Erase the bullet if it's off-screen
            bullets.erase(bullets.begin() + i);
        }
        else if (bullets[i].checkCollision(entities))
        {
            Entity explozieEntity = Entity(bullets[i].getPos(), explosionTextures[0]);
            explosions.emplace_back(explozieEntity, currentTime, 0.15f, explosionTextures); // 0.9 second duration
            bullets.erase(bullets.begin() + i);
        }
        
    }

    for (int i = explosions.size() - 1; i >= 0; --i) {
        explosions[i].update(currentTime);
        if (explosions[i].isFinished(currentTime)) {
            explosions.erase(explosions.begin() + i);
        } else {
            window.render(explosions[i].entity);
        }
    }

    window.render(player);
    window.render(cursor);

    // Render bullets
    for (auto& bullet : bullets) {
        window.render(bullet);
    }

    window.display();

    int frameTicks = SDL_GetTicks() - startTicks;
    if(frameTicks < 1000 / window.getRefreshRate())
        SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
    }
    window.cleanUp();
    SDL_Quit();
    return 0;

}