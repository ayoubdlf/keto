#ifndef GAME_HPP
#define GAME_HPP

#include <raylib.h>
#include <fstream>
#include "utils.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "map.hpp"
#include "bullet.hpp"
#include "levels.hpp"
#include "menu.hpp"

class Game {
    private:
        Player player;
        std::vector<Enemy> enemies;
        Levels levels;
        Map map;
        Menu menu;

        Font font;

        Texture2D target; // custom cursor
        Camera2D camera;
        Camera2D fixedCamera;

        AlertMessage alertMessage;

        void draw();
        void loadTextures();
        void updateCamera();
        void drawTarget();
        void drawLevelNumber();

        static Game* instance;
    public:
        static Game* getInstance();
        Game(int width, int height);
        ~Game();
        void init();
        void reset(bool resetLevels = true);
        void input();
        void update();
        void render();
        void load();
        void save();
        void nextLevel();
        state getState();

        void alert(std::string message);
        Camera2D getCamera();
        Camera2D getFixedCamera();
        Map& getMap();
        Player& getPlayer();
        Levels& getLevels();
        std::vector<Enemy>& getEnemies();
        Font& getFont();
        
};


#endif // GAME_HPP
