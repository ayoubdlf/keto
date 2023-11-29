#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <raylib.h>
#include "utils.hpp"

using namespace utils;

class Menu {
    private:
        std::vector<Texture2D> texturesStart;
        std::vector<Texture2D> texturesLevelSelection;
        std::vector<Texture2D> texturesGameOver;
        std::vector<Texture2D> texturesPlaying;

        utils::state state;
        
        void drawStart();
        void drawLevels();
        void drawGameOver();
        void drawPlaying();

        void updateStart();
        void updateLevels();
        void updateGameOver();
        void updatePlaying();
    public:
        Menu();
        ~Menu();
        void draw();
        void update();
        void loadTexture();
        utils::state getState();
};

#endif // MENU_HPP