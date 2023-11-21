#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <iostream>
#include <raylib.h>
#include "sprite.hpp"

using namespace utils;

class Enemy : public Sprite {
    private:
        Direction direction; // Enemy direction: left or right
        int currentFrame;
        int framesCounter;
        int framesSpeed;
        std::array<ActionTexture, 4> textures;

        ActionTexture loadActionTexture(std::string path);
        void handleCollisions();
    public:
        Enemy();
        void draw();
        void update();
        void updateFrames();
        void updateBrain();
        void setPosition(Vector2 position);
        void loadTextures();
        Vector2 getPosition();
};

#endif // ENEMY_HPP
