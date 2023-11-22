#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <raylib.h>
#include "sprite.hpp"

using namespace utils;

class Player : public Sprite {
    private:
        bool isJumping;
        
        Direction direction; // Player direction: left or right
        int currentFrame;
        int framesCounter;
        int framesSpeed;
        std::array<ActionTexture, 4> textures;
        Texture2D tag;

        ActionTexture loadActionTexture(std::string path);
        void handleCollisions();
    public:
        Player();
        void handleInputs();
        void draw();
        void update();
        void updateFrames();
        Vector2 getPosition();
        void loadTextures();
        void drawTag();
};


#endif // PLAYER_HPP
