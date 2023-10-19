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
        Destination destination;
        float speed = 2.5f;
        bool isColliding;
        std::string name;
        Texture2D texture;
    public:
        Player(std::string name="keto");
        ~Player();
        void handleInputs();
        void draw();
        void update();
        void colliding();
        Vector2 getPosition();
        Vector2 getDestination();
        Sprite getRect(Vector2 position);
        void loadTexture();
        void unloadTexture();
};


#endif // PLAYER_HPP
