#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <iostream>
#include <raylib.h>
#include <stack>
#include "utils.hpp"
#include "../include/camera.hpp"

using namespace utils;

enum Weapons {
    Nothing = 0,
    Gun     = 1,
    Sword   = 2
    // Granade ?
};

class Weapon {
    private:
        Weapons   type;
        Texture2D texture;
        Vector2   position;
        std::stack<int> myStack;
        void drawGun(Direction direction, Direction look);
        void drawSword(Direction direction, Direction look);
    public:
        Weapon();
        ~Weapon();
        void useWeapon(Weapons weapon);
        void throwWeapon();
        void setPosition(Vector2 position);
        void draw(Direction direction, utils::Direction look); // If (direction || look) == Left, flip the gun to the other side
        void loadTexture();
        void unloadTexture();
        void createStack();
        bool isEmpty();
};


#endif // WEAPON_HPP
