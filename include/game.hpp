#ifndef GAME_HPP
#define GAME_HPP

#include <raylib.h>
#include "utils.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "map.hpp"
#include "bullet.hpp"

class Game {
    private:
        Player player;
        std::vector<Enemy> enemies;
        Map map;
        
        Camera2D camera;

        void draw();
        void loadTextures();

        static Game* instance;
    public:
        static Game* getInstance();
        Game(int width, int height);
        ~Game();
        void init();
        void input();
        void update();
        void render();
        void updateCamera();

        Camera2D getCamera();
        std::vector<Tile>& getObstacles();
        Player& getPlayer();
        std::vector<Enemy>& getEnemies();
};


#endif // GAME_HPP
