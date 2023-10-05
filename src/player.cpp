#include <iostream>
#include <raylib.h>
#include "../include/player.hpp"

Player::Player(std::string name) {
    this->name = name;
    this->position.x = 0;
    this->position.y = 0;
}

Player::~Player() {
    this->unloadTexture();
}

void Player::draw() {
    DrawTexture(this->texture, this->position.x, this->position.y, BLACK);
}

void Player::handleInputs() {
    if (IsKeyDown(KEY_RIGHT)) {
        this->position.x += this->speed;
    }

    if (IsKeyDown(KEY_LEFT)) {
        this->position.x -= this->speed;
    }

    if (IsKeyDown(KEY_UP)) {
        this->position.y -= this->speed;
    }

    if (IsKeyDown(KEY_DOWN)) {
        this->position.y += this->speed;
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
