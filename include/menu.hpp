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

namespace menuTextures {
    enum state {
        Welcome        = 0,
        LevelSelection = 1,
        GameOver       = 2
    };
};


class Menu {
    private:
        std::vector<Texture2D> texturesWelcome;
        std::vector<Texture2D> texturesLevelSelection;
        std::vector<Texture2D> texturesGameOver;

        menuState::state state;

    public:
        Menu();
        ~Menu();

        void drawWelcome();
        void drawLevels();
        void drawGameOver();
        void draw();

        void update();
        void updateWelcome();
        void updateLevels();
        void updateGameOver();

        void loadTexture();
};

#endif // MENU_HPP