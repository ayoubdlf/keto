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

        int brainCounter; // will help use to determine when the enemy will shoot
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
