// #pragma once
// #include "RenderWindow.hpp"
// #include "Player.hpp"
// #include "Cursor.hpp"
// #include "Bullet.hpp"
// #include "Explozie.hpp"
// #include "Enemy.hpp"
// #include "RenderText.hpp"
// #include "RenderText.hpp"
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL_ttf.h>
// #include <vector>
// #include <string>
// #include <string>
// #include <string.h>

// enum class GameState {
//     Playing,
//     Dead,
//     Exit,
//     MainMenu
// };

// class GameStateManager {
// public:
//     GameStateManager(RenderWindow& window);
//     void runGameLoop();

// private:
//     RenderWindow& window;
//     GameState gameState;
//     Player player;
//     std::vector<SDL_Texture*> playerTextures;
//     float spawnTimer;
//     const int WIDTH = 1920, HEIGHT = 1080;

//     void initialize_Playing();
//     void loadResources();
//     void update(float deltaTime);
//     void render();
//     void reset_Game();
//     void handleDeathScreenState();


//     void GameStateManager::renderDeathScreen() {
//     // Clear the screen with a dark background to indicate game over
//     SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 255); // Black color
//     SDL_RenderClear(window.getRenderer());

//     // Render the "Game Over" message
//     RenderText gameOverText(window.getRenderer(), "path/to/font.ttf", 48); // Adjust font path and size
//     SDL_Color textColor = {255, 255, 255, 255}; // White color
//     gameOverText.display("Game Over! Press 'R' to retry.", 300, 300, textColor); // Adjust position and color

//     // Update the window with the new rendering
//     SDL_RenderPresent(window.getRenderer());
// }
// };
