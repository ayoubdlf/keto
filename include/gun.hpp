#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <iostream>
#include <raylib.h>
#include "utils.hpp"
#include "bullet.hpp"

using namespace utils;

namespace shooter {
    enum type {
        Player = 0,
        Enemy  = 1,
    };
};

class Gun {
    private:
        Texture2D     texture;
        Vector2       position;
        bool          available;
        bool          canShoot; // To avoid the shooter shooting himself
        shooter::type shooter;

        Rectangle source;
        Rectangle dest;
        Vector2   origin;
        float     rotation;
        float     scale;

        /* Bullets */
        int bulletsLeft;
        std::vector<Bullet> bullets;

        void updateBullets();
    public:
        Gun();
        ~Gun();
        void useGun(shooter::type shooter);
        void throwGun();
        void update(Vector2 position);
        void draw();
        void fire();
        void load(int nbBullets);
        void loadTexture();
        int  getBulletsLeft();
        void updatePlayerBehaviour(Vector2 position);
        void updateEnemyBehaviour(Vector2 position);
};


#endif // WEAPON_HPP
