#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <raylib.h>
#include "utils.hpp"

using namespace utils;

namespace menu {
    enum textures {
        Start = 0,
        Play  = 1,
        Load  = 2,
        Retry = 3,
        Exit  = 4
    };
}

struct texture {
    Texture2D texture;
    float scale;
    Vector2 position;
};

class Menu {
    private:
        std::array<texture, 5> textures;

        utils::state state;
        int counter;
        
        void drawStart();
        void drawCompleted();
        void drawLevels();
        void drawGameOver();
        void drawPlaying();

        void updateStart();
        void updateCompleted();
        void updateLevels();
        void updateGameOver();
        void updatePlaying();
    public:
        Menu();
        ~Menu();
        void draw();
        void update();
        void loadTextures();
        utils::state getState();
        void setState(utils::state state);
};

#endif // MENU_HPP