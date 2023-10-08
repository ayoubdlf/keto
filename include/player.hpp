#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <raylib.h>
#include "utils.hpp"

using namespace utils;

class Player {
    private:
        Position position = {0, 0};
        std::string name;
        Texture2D texture;
        float speed = 2.5f;
    public:
        Player(std::string name="keto");
        ~Player();
        void draw();
        void handleInputs();
        Position getPosition();
        void loadTexture();
        void unloadTexture();
};


#endif // PLAYER_HPP
