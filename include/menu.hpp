#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <raylib.h>
#include "utils.hpp"

using namespace utils;

namespace menu {
    enum textures {
        Keto     = 0, // Title
        Play     = 1,
        Load     = 2,
        Save     = 3,
        Pause    = 4,
        Skins    = 5,
        Left     = 6,
        Right    = 7,
        GameOver = 8,
        End      = 9,
        Exit     = 10
    };
}

struct texture {
    Texture2D texture;
    float scale;
    Vector2 position;
};

class Menu {
    private:
        std::array<texture, 11> textures;
        std::vector<texture> skins;
        std::vector<std::string> skinsName;

        utils::state state;
        int counter;
        int currentSkin;
        
        void drawStart();
        void drawPlaying();
        void drawPause();
        void drawSkins();
        void drawCompleted();
        void drawGameOver();

        void updateStart();
        void updatePlaying();
        void updatePause();
        void updateSkins();
        void updateCompleted();
        void updateGameOver();

        void loadSkins();
        bool isButtonHovered(texture texture);
        bool isButtonClicked(texture texture);
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