#ifndef GAME_HPP
#define GAME_HPP

#include "player.hpp"
#include "map.hpp"
#include "utils.hpp"

class Game {
    private:
        Player player;
        Map map;
        Camera2D camera;
        void draw();
        void collisions();
    public:
        Game(int width, int height);
        ~Game();
        void input();
        void update();
        void render();
        void updateCamera();
        void loadTextures();
};


#endif // GAME_HPP
