#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <raylib.h>
#include <array>
#include <stack>  
#include "weapon.hpp"
#include "map.hpp"

using namespace utils;

enum Action {
    Idle    = 1,
    Run     = 2,
    Jump    = 3,
    Death   = 4
};

struct ActionTexture {
    Texture2D texture;
    Rectangle frames;
};

class Player {
    private:
        float width;
        float height;
        Vector2 position;
        Vector2 velocity;
        bool isJumping;
        std::string name;
        std::stack<int> lifeBar;
        
        /*  Player  */
        int action; // idle, running, jumping, death
        Direction direction; // Player direction left or right
        Direction looking;   // Player looking at the left or right
        int currentFrame;
        int framesCounter;
        int framesSpeed;
        std::array<ActionTexture, 5> textures;

        /*  Weapon  */
        Weapon weapon;

        /*  Functions  */
        ActionTexture loadActionTexture(std::string path);
        void handleCollisions();
    public:
        Player();
        ~Player();
        float getWidth();
        float getHeight();
        void setPlayer(std::string name="keto");
        void handleInputs();
        void draw();
        void update();
        Vector2 getPosition();
        Vector2 getVelocity();
        void loadTextures();
        void damage();
        bool isAlive();
};


#endif // PLAYER_HPP
