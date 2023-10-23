#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <raylib.h>
#include "utils.hpp"

using namespace utils;

class Player {
    private:
        Vector2 position;
        Vector2 velocity;
        bool isJumping;
        std::string name;
        Texture2D texture;
    public:
        Player(std::string name="keto");
        ~Player();
        void handleInputs();
        void draw();
        void update();
        void isColliding(std::string axis, float value);
        Vector2 getPosition();
        Vector2 getVelocity();
        void loadTexture();
        void unloadTexture();
};


#endif // PLAYER_HPP
