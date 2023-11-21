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

struct ActionTexture {
    Texture2D texture;
    Rectangle frames;
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

        int action; // idle, running, jumping, dead
        
        Gun gun;
    public:
        Sprite();
        ~Sprite();
        void setName(std::string name="keto");
        Vector2 getPosition();
        void updatePosition();
        void heal(int health);
        void damage(int damage);
        int getHealth();
        bool isAlive();
        Rectangle getRect();
        void drawHealthBar();
};


#endif // SPRITE_HPP
