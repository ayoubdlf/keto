#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <raylib.h>
#include "weapon.hpp"

using namespace utils;

enum Action {
    Idle    = 1,
    Run     = 2,
    Jump    = 3
};

struct ActionTexture {
    Texture2D texture;
    Rectangle frames;
};

class Player {
    private:
        Vector2 position;
        Vector2 velocity;
        bool isJumping;
        std::string name;
        
        /*  Player  */
        int action; // idle, running, jumping
        Direction direction; // Player direction left or right
        Direction looking;   // Player looking at the left or right
        int currentFrame;
        int framesCounter;
        int framesSpeed;
        std::array<ActionTexture, 4> textures;

        /*  Weapon  */
        Weapon weapon;

        /*  Functions  */
        ActionTexture loadActionTexture(std::string path);
    public:
        Player();
        ~Player();
        void setPlayer(std::string name="keto");
        void handleInputs();
        void draw();
        void update();
        void isColliding(std::string axis, float value);
        Vector2 getPosition();
        Vector2 getVelocity();
        void loadTextures();
        void unloadTextures();
};


#endif // PLAYER_HPP
