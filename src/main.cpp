#include <raylib.h>
#include "../include/game.hpp"

// #define WIDTH 800
// #define HEIGHT 800

#define WIDTH 640
#define HEIGHT 320

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