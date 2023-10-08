#include <raylib.h>
#include "../include/game.hpp"

int main() {

    Game game = Game(WIDTH, HEIGHT);

    game.loadTextures();
    
    while (!WindowShouldClose()) {

        game.input();
        game.update();
        game.render();

    }

    game.clean();
    CloseWindow();
    
    return 0;
}