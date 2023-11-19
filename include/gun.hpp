#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <iostream>
#include <raylib.h>
#include "utils.hpp"
#include "camera.hpp"
#include "bullet.hpp"
#include <stack>

using namespace utils;

class Gun {
    private:
        Texture2D texture;
        Vector2   position;
        bool      available;

        Rectangle source;
        Rectangle dest;
        Vector2   origin;
        float     rotation;
        float     scale;

        /* Bullets */
        int nbBullets;
        std::vector<Bullet> bullets;
    public:
        Gun();
        ~Gun();
        void useGun();
        void throwGun();
        void update(Vector2 position);
        void draw();
        void fire();
        void load(int nbBullets);
        bool isAvailable();
        void loadTexture();
};


#endif // WEAPON_HPP
