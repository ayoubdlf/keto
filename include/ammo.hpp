#ifndef AMMO_HPP
#define AMMO_HPP

#include <iostream>
#include <raylib.h>
#include "utils.hpp"
#include "map.hpp"

using namespace utils;

// enum AmmoType {
//     Nothing = 0,
//     Gun     = 1,
//     Sword   = 2
// };

class Ammo {
    private:
        // AmmoType   type;
        float width;
        float height;
        Texture2D texture;
        Vector2   position;
    public:
        Ammo();
        ~Ammo();
        void draw(); 
        void loadTexture();
        void unloadTexture();
        bool isThereACollision();
};


#endif // AMMO_HPP
