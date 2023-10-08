#ifndef GAME_HPP
#define GAME_HPP

#include "player.hpp"
#include "map.hpp"
#include "utils.hpp"

class Game {
    private:
        int width;
        int height;
        Player player;
        Map map;
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


#endif // GAME_HPP
