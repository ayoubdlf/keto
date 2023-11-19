#ifndef BULLET_HPP
#define BULLET_HPP

#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include "utils.hpp"
#include "camera.hpp"

using namespace utils;

class Bullet {
    private:
        Texture2D texture;
        Vector2   position;
        float     rotation;
        float     angle;
        float     scale;
        bool      active;
    public:
        Bullet();
        ~Bullet();
        void draw();
        void update();
        void fire(Vector2 position, float angle);
        bool isActive();
        void handleCollision();
        void loadTexture();
};


#endif // BULLET_HPP
