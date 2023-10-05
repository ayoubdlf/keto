#pragma once
#include <iostream>
#include <raylib.h>

class Player {
    private:
        Vector2 position;
        std::string name;
        Texture2D texture;
        float speed = 2.5f;
    public:
        Player(std::string name="keto");
        ~Player();
        void draw();
        void handleInputs();
        Vector2 getPosition();
        void loadTexture();
        void unloadTexture();
};
