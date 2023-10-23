#include <iostream>
#include <raylib.h>
#include "../include/player.hpp"

Player::Player(std::string name) {
    this->name      = name;
    this->position  = {0.0f, 0.0f};
    this->velocity  = {0.0f, 0.0f};
    this->isJumping = false;
}

Player::~Player() {
    this->unloadTexture();
}

void Player::draw() {
    DrawTexture(this->texture, this->position.x, this->position.y, BLACK);
}

void Player::update() {
    this->velocity.y += GRAVITY;
    this->position.x += this->velocity.x;
    this->position.y += this->velocity.y;
}

void Player::handleInputs() {
    this->velocity = {0.0f, this->velocity.y};

    if(IsKeyDown(KEY_RIGHT))                  { this->velocity.x =  X_VELOCITY * DELTA * SCALE; }
    if(IsKeyDown(KEY_LEFT))                   { this->velocity.x = -X_VELOCITY * DELTA * SCALE; }
    if(IsKeyDown(KEY_UP) && !this->isJumping) { this->velocity.y = -Y_VELOCITY * DELTA * SCALE; this->isJumping = true; }

}

Vector2 Player::getPosition() {
    return this->position;
}

Vector2 Player::getVelocity() {
    return this->velocity;
}

void Player::isColliding(std::string axis, float value) {

    if(axis == "xAxis") {
        this->velocity.x = 0;
        this->position.x = (this->position.x > value) ? value + TILE_SIZE : value - TILE_SIZE;
    }
    
    if(axis == "yAxis") {
        // Head (collisions with the player head)
        if (this->velocity.y < 0) {
            this->velocity.y = 0;
            this->position.y = value + TILE_SIZE;
        }

        // Feet (collisions with the player feets)
        if (this->velocity.y > 0) {
            this->velocity.y = 0;
            this->position.y = value - TILE_SIZE;
            this->isJumping = false;
        }
    }

}

void Player::loadTexture() {
    std::string filePath = "assets/players/textures/" + this->name + ".png";
    this->texture = LoadTexture(filePath.c_str());
}

void Player::unloadTexture() {
    UnloadTexture(this->texture);
}
