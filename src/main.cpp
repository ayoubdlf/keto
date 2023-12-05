#include "../include/game.hpp"

int main() {

    Game::getInstance()->init();
    
    while (!WindowShouldClose() && Game::getInstance()->getMenu().getState() != utils::Exit) {

        Game::getInstance()->input();
        Game::getInstance()->update();
        Game::getInstance()->render();

    }
    
    CloseAudioDevice();
    CloseWindow();
        
    return EXIT_SUCCESS;
}