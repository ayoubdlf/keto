#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <raylib.h>
#include <random>
#include "sprite.hpp"

using namespace utils;

struct healthBar {
    Texture2D left;
    Texture2D middle;
    Texture2D middle_empty;
    Texture2D right;
    
    Texture2D hp_logo;
};

struct stats {
    int health;
    int kills;
    int bullets; // bulletsLeft
    int coins;
};

class Player : public Sprite {
    private:
        int kills;
        int coins;

        bool isJumping;
        
        Direction direction; // Player direction: left or right
        int currentFrame;
        int framesCounter;
        int framesSpeed;

        Texture2D tagTexture;
        Texture2D killsTexture;
        Texture2D bulletsTexture;
        Texture2D coinsTexture;
        healthBar healthBarTexture;
        std::array<Texture2D, 10> numbersTexture;

        void handleCollisions();
        void drawTag();
        void drawHealthBar();
        void drawKills();
        void drawBullets();
        void drawCoins();
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
        stats getStats();
        void loadData(json data);
};


#endif // PLAYER_HPP
