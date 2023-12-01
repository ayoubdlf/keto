#include "../include/game.hpp"

int main() {

    Game::getInstance()->init();
    
    while (!WindowShouldClose() && Game::getInstance()->getState() != Exit) {

        Game::getInstance()->input();
        Game::getInstance()->update();
        Game::getInstance()->render();

    }
    
    CloseWindow();
        
    return EXIT_SUCCESS;
}