#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <raylib.h>
#include "utils.hpp"

using namespace utils;

enum Action {
    Nothing = 0,
    Idle    = 1,
    Run     = 2,
    Jump    = 3
};

struct PlayerTexture {
    Texture2D texture;
    Rectangle frames;
};

class Player {
    private:
        Vector2 position;
        Vector2 velocity;
        bool isJumping;
        std::string name;

        int action; // What's the player doing: idle, running, jumping...
        std::string direction; // Left or Right only
        int currentFrame;
        int framesCounter;
        int framesSpeed;
        std::array<PlayerTexture, 4> textures;

        PlayerTexture loadPlayerTexture(std::string path);
    public:
        Player();
        ~Player();
        void setPlayer(std::string name="keto");
        void handleInputs();
        void draw();
        void update();
        void isColliding(std::string axis, float value);
        Vector2 getPosition();
        Vector2 getVelocity();
        void loadTextures();
        void unloadTextures();
};


#endif // PLAYER_HPP
