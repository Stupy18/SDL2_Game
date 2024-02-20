#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"
#include "Background.hpp"
#include "Player.hpp"
#include "Cursor.hpp"
#include "Bullet.hpp"
#include "Explozie.hpp"
#include "Enemy.hpp"
#include "RenderText.hpp"

enum class GameState {
    Playing,
    Dead,
    Exit,
    MainMenu,
    Loading
};

bool fadeEffectApplied = false;

const int WIDTH = 1920, HEIGHT = 1080;

int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) > 0) {
        cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << endl;
    }

    if (!(IMG_Init(IMG_INIT_PNG))) {
        cout << "IMG_Init has failed. Error: " << SDL_GetError() << endl;
    }

    RenderWindow window("GAME v1.0", WIDTH, HEIGHT);
    SDL_SetWindowFullscreen(window.getWindow(), SDL_WINDOW_FULLSCREEN);
    int windowRefreshRate = window.getRefreshRate();
    RenderText renderText(window.getRenderer(), "src/res/fonts/ccoverbyteoffregular.otf", 40);

    SDL_Texture* diceTexture1 = window.loadTexture("src/res/images/dice_1.png");
    SDL_Texture* diceTexture2 = window.loadTexture("src/res/images/dice_2.png");
    SDL_Texture* diceTexture3 = window.loadTexture("src/res/images/dice_3.png");
    SDL_Texture* backgroundTexture = window.loadTexture("src/res/images/casino_background.png");
    SDL_Texture* MainMenubackgroundTexture = window.loadTexture("src/res/images/MainMenu_background.png");
    SDL_Texture* playerTexture_left = window.loadTexture("src/res/images/character_stanga.png");
    SDL_Texture* playerTexture_right = window.loadTexture("src/res/images/character_dreapta.png");
    vector<SDL_Texture*> playerTextures = {playerTexture_right, playerTexture_left};
    SDL_Texture* cursorTexture = window.loadTexture("src/res/images/cursor.png");
    SDL_Texture* bulletTexture = window.loadTexture("src/res/images/bullet.png");
    SDL_Texture* explozieTexture1 = window.loadTexture("src/res/images/explozie.png");
    SDL_Texture* explozieTexture2 = window.loadTexture("src/res/images/explozie2.png");
    SDL_Texture* explozieTexture3 = window.loadTexture("src/res/images/explozie3.png");
    SDL_Texture* enemyTexture = window.loadTexture("src/res/images/enemy_atm.png");
    SDL_Texture* HPTexture = window.loadTexture("src/res/images/HP_ICON2.png");

    

    SDL_SetTextureBlendMode(backgroundTexture, SDL_BLENDMODE_BLEND);
    // Example: To give a darker, night-time look
    SDL_SetTextureColorMod(backgroundTexture, 128, 128, 128); // Adjust RGB values as needed
    SDL_SetTextureAlphaMod(backgroundTexture, 230); // Adjust alpha value (0-255) as needed
    // SDL_Texture* fogTexture = window.loadTexture("src/res/images/fog.png");
    // SDL_SetTextureBlendMode(fogTexture, SDL_BLENDMODE_BLEND);
    // // For smoke
    // SDL_SetTextureColorMod(fogTexture, 128, 128, 128); // Darken for smoke effect



    SDL_SetTextureAlphaMod(MainMenubackgroundTexture, 200);


    Background background(backgroundTexture, 1920, 1080);
    // Background fog(fogTexture, 1920, 1080);
    Background MainMenubackground(MainMenubackgroundTexture, 1920, 1080);
    int spawnInterval = 5; // Time in seconds between each enemy spawn
    float spawnTimer = spawnInterval; // Timer starts at the interval

    Player player(Vector2f(100, 780), playerTextures, 2.5, WIDTH, HEIGHT);
    player.setFrameSize(80, 80, 0, 0);
    SDL_ShowCursor(SDL_DISABLE);

    Cursor cursor({0, 0}, cursorTexture);
    cursor.setFrameSize(62, 62, 0, 0);

    Entity HP(Vector2f(20, 10), HPTexture);
    HP.setFrameSize(80, 80, 0, 0);

    vector<Bullet> bullets;
    vector<Explosion> explosions;
    vector<SDL_Texture*> explosionTextures = {explozieTexture1, explozieTexture2, explozieTexture3};
    vector<Enemy> enemies;

 std::vector<Entity> entities = {
                            Entity(Vector2f(0,800),diceTexture1),
                            // Entity(Vector2f(400,600),grassTexture1),
                            // Entity(Vector2f(528,600),grassTexture1),
                            // Entity(Vector2f(656,600),grassTexture1),
                            Entity(Vector2f(128,800),diceTexture3),
                            Entity(Vector2f(256,800),diceTexture3),
                            Entity(Vector2f(600,800),diceTexture2), 
                            Entity(Vector2f(728,800),diceTexture3), 
                            Entity(Vector2f(1000,800),diceTexture2),
                            Entity(Vector2f(1128,800),diceTexture1),
                            Entity(Vector2f(1256,800),diceTexture3),
                            Entity(Vector2f(1536,800),diceTexture2),
                            Entity(Vector2f(1664,800),diceTexture3),
                            Entity(Vector2f(1792,800),diceTexture3)

                            };

    GameState gameState = GameState::MainMenu;
    bool transitionToLoading = false;
    bool gameRunning = true;
    SDL_Event event;
    const float timeStep = 0.01f;
    float accumulator = 0.0f;
    float currentTime = utils::hireTimeInSeconds();

    while (gameRunning) {
        switch (gameState) {
           case GameState::MainMenu: {
                SDL_ShowCursor(SDL_ENABLE);
                window.clear();
                SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 255); // Black background color
                SDL_RenderClear(window.getRenderer());

                // Display background
                window.renderBackground(MainMenubackground);

                // Display "Play" button
                SDL_Rect playButton = {WIDTH / 8, HEIGHT / 2 + 200, 200, 60}; // x, y, width, height
                SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 255); // Black button color
                SDL_RenderFillRect(window.getRenderer(), &playButton); // Fill button with solid color

                // Display "Options" button
                SDL_Rect optionsButton = {WIDTH / 8, HEIGHT / 2 + 280, 200, 60}; // x, y, width, height
                SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 255); // Black button color
                SDL_RenderFillRect(window.getRenderer(), &optionsButton); // Fill button with solid color

                // Draw button text
                renderText.display("Play", playButton.x + 60, playButton.y + 7 , {255, 255, 255, 255}); // White text color, adjust text position as needed
                renderText.display("Options", optionsButton.x + 30, optionsButton.y + 7 , {255, 255, 255, 255}); // White text color, adjust text position as needed

                // Draw button outline (optional)
                SDL_SetRenderDrawColor(window.getRenderer(), 255, 255, 255, 255); // White outline color
                SDL_RenderDrawRect(window.getRenderer(), &playButton);
                // Draw button outline (optional)
                SDL_SetRenderDrawColor(window.getRenderer(), 255, 255, 255, 255); // White outline color
                SDL_RenderDrawRect(window.getRenderer(), &optionsButton);

                SDL_RenderPresent(window.getRenderer());

                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        gameRunning = false;
                    } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                        int mouseX, mouseY;
                        SDL_GetMouseState(&mouseX, &mouseY);

                        // Check if click is inside the play button
                        if (mouseX >= playButton.x && mouseX <= playButton.x + playButton.w &&
                            mouseY >= playButton.y && mouseY <= playButton.y + playButton.h) {
                            SDL_ShowCursor(SDL_DISABLE);
                            window.applyFadeEffect(window.getRenderer(), 0, 255, 30); // Fade out
                            gameState = GameState::Loading;
                            transitionToLoading = true;
                            fadeEffectApplied = false;  // Reset the fade effect flag
                            // Reset game elements for new game
                            player.reset_stats(); // Reset player stats and position
                            enemies.clear();
                            bullets.clear();
                            explosions.clear();
                        }
                    }
                }
                break;
            }
            case GameState::Loading: {
                        if (transitionToLoading) {
                            window.applyFadeEffect(window.getRenderer(), 0, 255, 30); // Fade to black
                            renderText.display("Loading...", WIDTH / 2 -100, HEIGHT / 2, {255, 255, 255, 255});
                            SDL_RenderPresent(window.getRenderer());
                            SDL_Delay(2000); // Hold the loading screen for a moment
                            window.applyFadeEffect(window.getRenderer(), 255, 0, 30); // Fade out
                            transitionToLoading = false;
                            gameState = GameState::Playing;
                        }
                        break;
            }
            case GameState::Playing: {
                SDL_ShowCursor(SDL_DISABLE);
                window.clear();
                if (!fadeEffectApplied) {
                // Apply fade effect only once
                window.applyFadeEffect(window.getRenderer(), 255, 0, 30); // Fade in
                fadeEffectApplied = true;
            }
                int startTicks = SDL_GetTicks();
                float newTime = utils::hireTimeInSeconds();
                float frameTime = newTime - currentTime;
                
                currentTime = newTime;

                // Calculate deltaTime
                float deltaTime = frameTime;

                // Update player's reload timer
                player.updateReloadTimer(deltaTime);

                accumulator += frameTime;

                while (accumulator >= timeStep) {
                    while (SDL_PollEvent(&event)) {
                        if (event.type == SDL_QUIT) {
                            gameRunning = false;
                        }

                        player.handleInput(event);

                        // Check for mouse click to spawn a bullet and ensure player is not reloading
                        if (event.type == SDL_MOUSEBUTTONDOWN && !player.isCurrentlyReloading()) {
                            Vector2f cursorPos = cursor.getPos();
                            Vector2f playerPos = player.getPos();
                            player.is_ammoEmpty();
                            if (player.hasAmmo()) {
                                player.set_currentAmmo(player.get_currentAmmo() - 1);
                                bullets.emplace_back(playerPos, bulletTexture, cursorPos, 700.0f);
                            }
                        }

                        // Handle reload input
                        if (event.type == SDL_KEYDOWN) {
                            if (event.key.keysym.sym == SDLK_r && !player.isCurrentlyReloading()) {
                                player.startReloading();
                            }
                        }
                    }

                    accumulator -= timeStep;
                }

                const float alpha = accumulator / timeStep;
                window.clear();

                window.renderBackground(background);
                // window.renderBackground(fog);

                spawnTimer -= frameTime;

                // Check if it's time to spawn a new enemy
                if (spawnTimer <= 0) {
                    // Reset the spawn timer
                    spawnTimer = spawnInterval;
                    
                    // Spawn a new enemy
                    Vector2f enemySpawnPos = utils::getRandomSpawnPositionOutsideScreen(WIDTH, HEIGHT);
                    Enemy enemy(enemySpawnPos, enemyTexture, 1.3f,3);
                    enemy.setFrameSize(65,65,0,0);
                    enemies.emplace_back(enemy);
                }

                for (Enemy& enemy : enemies) {
                    enemy.update(player.getPos());
                    window.render(enemy);
                }

                SDL_Rect playerRect = {abs(int(player.getPos().x)), abs(int(player.getPos().y)+50), player.get_currentFrame().w-40, player.get_currentFrame().h-10};

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
                        player.set_Health(player.get_Health()-20);
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
                            bulletIt->setPos(bulletX-50.0f,bulletY-80.0f);

                            Entity explosionEntity = Entity(bulletIt->getPos(), explosionTextures[0]);
                            explosions.emplace_back(explosionEntity, currentTime, 0.15f, explosionTextures);

                            // Remove the bullet
                            bulletIt = bullets.erase(bulletIt);
                            enemyIt->takeDamage(player.get_Damage());
                            if (enemyIt->isDead())
                            {
                                // Remove the enemy
                            enemyIt = enemies.erase(enemyIt);
                            enemyRemoved = true; // Mark that the enemy was removed
                            }
                            
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

                window.render(HP);
                SDL_Color textColor = {0, 0, 0, 0}; // Black color
                SDL_Color textColorYellow = {255, 255, 0, 0}; // yellow color
                SDL_Color textColorWhite = {255, 255, 255, 255}; // white color
                renderText.display(to_string(player.get_Health()), 115, 40, textColorWhite); //30 10 for top left
                renderText.display(to_string(player.get_currentAmmo()) + "/" + to_string(player.get_totalAmmo()), 1780, 1000, textColorWhite);
                window.display();


                if (player.get_Health() <= 0) {
                    gameState = GameState::Dead;
                }

                int frameTicks = SDL_GetTicks() - startTicks;
                if (frameTicks < 1000 / windowRefreshRate) {
                    SDL_Delay(1000 / windowRefreshRate - frameTicks);
                }
                break;
            }
           case GameState::Dead: {
                SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 255); // Black color
                SDL_RenderClear(window.getRenderer());
                renderText.display("Game Over! Press 'H' to Retry", WIDTH / 2 - 300 , HEIGHT / 2, {255, 255, 255, 255}); // White color
                SDL_RenderPresent(window.getRenderer());

                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        gameRunning = false;
                    } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_h) {
                        gameState = GameState::MainMenu;
                    }
                }
                break;
            }
            // Other cases...
        }
    }

    window.cleanUp();
    SDL_Quit();
    return 0;
}
