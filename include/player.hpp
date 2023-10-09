#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <raylib.h>
#include "utils.hpp"

using namespace utils;

class Player {
    private:
        Vector2 position = {0.0f, 0.0f};
        Vector2 velocity = {0.0f, 0.0f};
        float speed = 2.5f;
        std::string name;
        Texture2D texture;
    public:
        Player(std::string name="keto");
        ~Player();
        void handleInputs();
        void draw();
        void update();
        Vector2 getPosition();
        void loadTexture();
        void unloadTexture();
};


#endif // PLAYER_HPP
