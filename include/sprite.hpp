#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <iostream>
#include <raylib.h>
#include <array>
#include "gun.hpp"
#include "map.hpp"

using namespace utils;

enum Action {
    Nothing = 0,
    Idle    = 1,
    Run     = 2,
    Jump    = 3
};

class Sprite {
    protected:
        std::string name;
        float width;
        float height;
        Vector2 position;
        Vector2 velocity;
        bool isJumping;
        int health;

        int action; // idle, running, jumping
        std::array<CustomTexture, 4> textures;
        
        Gun gun;
    public:
        Sprite();
        ~Sprite();
        void setName(std::string name = "keto");
        std::string getName();
        Vector2 getPosition();
        void updatePosition();
        void heal(int health);
        void damage(int damage);
        int getHealth();
        bool isAlive();
        Rectangle getRect();
        void drawHealthBar();
        CustomTexture loadCustomTexture(std::string path);
};


#endif // SPRITE_HPP
