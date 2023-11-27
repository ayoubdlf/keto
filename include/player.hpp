#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <raylib.h>
#include "sprite.hpp"

using namespace utils;

struct healthBar {
    Texture2D left;
    Texture2D middle;
    Texture2D middle_empty;
    Texture2D right;
    
    Texture2D hp_logo;
};

class Player : public Sprite {
    private:
        bool isJumping;
        int kills;
        
        Direction direction; // Player direction: left or right
        int currentFrame;
        int framesCounter;
        int framesSpeed;
        std::array<ActionTexture, 4> textures;

        Texture2D tagTexture;
        Texture2D killsTexture;
        Texture2D bulletsTexture;
        healthBar healthBarTexture;
        std::array<Texture2D, 10> numbersTexture;

        ActionTexture loadActionTexture(std::string path);
        void handleCollisions();
        void drawTag();
        void drawHealthBar();
        void drawKills();
        void drawBullets();
        void drawNumbers(Vector2 position, Texture2D texture, int value);
    public:
        Player();
        void handleInputs();
        void drawStats();
        void draw();
        void update();
        void updateFrames();
        Vector2 getPosition();
        void kill(); // When the player kills an enemy 
        void loadTextures();
};


#endif // PLAYER_HPP
