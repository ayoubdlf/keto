#ifndef BULLET_HPP
#define BULLET_HPP

#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include "utils.hpp"

using namespace utils;

class Bullet {
    private:
        Texture2D texture;
        Vector2   position;
        float     rotation;
        float     angle;
        float     scale;
        bool      active;
        shooter::type shooter;
    public:
        Bullet();
        ~Bullet();
        void draw();
        void update();
        void fire(shooter::type shooter, Vector2 position, float angle);
        bool isActive();
        void handleCollision();
        void loadTexture();
};


#endif // BULLET_HPP
