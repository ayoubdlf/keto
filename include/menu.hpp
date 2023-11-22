#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <raylib.h>
#include "utils.hpp"

using namespace utils;

namespace menuState {
    enum state {
        Welcome        = 0,
        LevelSelection = 1,
        GameOver       = 2
    };
};


class Menu {
    private:
        std::vector<Texture2D> textures;
        menuState::state state;

    public:
        Menu();
        ~Menu();

        void drawWelcome();
        void drawLevels();
        void drawGameOver();
        void draw();

        void update();
        void loadTexture();
};

#endif // MENU_HPP