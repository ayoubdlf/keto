#ifndef GAME_HPP
#define GAME_HPP

#include <raylib.h>
#include <fstream>
#include "utils.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "map.hpp"
#include "bullet.hpp"

class Game {
    private:
        int level;
        Player player;
        std::vector<Enemy> enemies;
        Map map;
        Texture2D target; // custom cursor
        Camera2D camera;
        Camera2D fixedCamera;

        AlertMessage alertMessage;

        void draw();
        void loadTextures();
        void updateCamera();
        void drawTarget();

        static Game* instance;
    public:
        static Game* getInstance();
        Game(int width, int height);
        ~Game();
        void init();
        void input();
        void update();
        void render();
        void load();
        void save();

        void alert(std::string message);
        Camera2D getCamera();
        Map& getMap();
        Player& getPlayer();
        std::vector<Enemy>& getEnemies();
        
};


#endif // GAME_HPP
