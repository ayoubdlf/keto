#ifndef GAME_HPP
#define GAME_HPP

#include "utils.hpp"
#include "player.hpp"
#include "camera.hpp"
#include "map.hpp"

class Game {
    private:
        Player player;
        Map map;
        void draw();
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
