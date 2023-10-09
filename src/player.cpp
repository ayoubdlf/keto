#include <iostream>
#include <raylib.h>
#include "../include/player.hpp"

Player::Player(std::string name) {
    this->name = name;
}

Player::~Player() {
    this->unloadTexture();
}

void Player::draw() {
    DrawTexture(this->texture, this->position.x, this->position.y, BLACK);
}

void Player::update() {
    this->position.x += this->velocity.x;
    this->position.y += this->velocity.y;
}

void Player::handleInputs() {
    this->velocity = {0, 0};

    if (IsKeyDown(KEY_RIGHT) && this->position.x + TILE_SIZE < WIDTH) {
        this->velocity.x = this->speed;
    }
    if(IsKeyDown(KEY_LEFT) && this->position.x > 0) {
        this->velocity.x = -this->speed;
    }
    if (IsKeyDown(KEY_UP) && this->position.y > 0) {
        this->velocity.y = -this->speed;
    }
    if(IsKeyDown(KEY_DOWN) && this->position.y + TILE_SIZE < HEIGHT) {
        this->velocity.y = this->speed;
    }

}


Vector2 Player::getPosition() {
    return this->position;
}

void Player::loadTexture() {
    std::string filePath = "assets/players/textures/" + this->name + ".png";
    this->texture = LoadTexture(filePath.c_str());
}

void Player::unloadTexture() {
    UnloadTexture(this->texture);
}
