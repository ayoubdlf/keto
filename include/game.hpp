#pragma once
#include "player.hpp"

class Game {
    private:
        int width;
        int height;
        Player player;
        void draw();
        void unloadTextures();
    public:
        Game(int width, int height);
        ~Game();
        void input();
        void update();
        void render();
        void loadTextures();
        void clean();
};
