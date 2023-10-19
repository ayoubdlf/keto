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
    this->position.x = this->destination.x;
    this->position.y = this->destination.y;
}

void Player::handleInputs() {
    this->velocity    = { this->velocity.x, this->velocity.y }; // TODO: check of there is bug doing this
    this->isColliding = false;
    this->destination = { false, false, false, false, this->position.x, this->position.y };
    
    this->destination.right = IsKeyDown(KEY_RIGHT) && this->position.x + TILE_SIZE < WIDTH;
    this->destination.left  = IsKeyDown(KEY_LEFT) && this->position.x > 0;
    this->destination.up    = IsKeyDown(KEY_UP) && this->position.y > 0;
    this->destination.down  = IsKeyDown(KEY_DOWN) && this->position.y + TILE_SIZE < HEIGHT;

    if(this->destination.left)  {
        this->velocity.x    = -this->speed;
        this->destination.x = this->position.x + this->velocity.x;
    }

    if(this->destination.right) {
        this->velocity.x    = this->speed;
        this->destination.x = this->position.x + this->velocity.x;
    }

    if(this->destination.up)    {
        this->velocity.y    = -this->speed;
        this->destination.y = this->position.y + this->velocity.y;
    }

    if(this->destination.down)  {
        this->velocity.y    = this->speed;
        this->destination.y = this->position.y + this->velocity.y;
    }

}

Vector2 Player::getPosition() {
    return this->position;
}

Sprite Player::getRect(Vector2 position) {
    return {
        .position = position,
        .width = TILE_SIZE,
        .height = TILE_SIZE
    };
}

Vector2 Player::getDestination() {
    return { this->destination.x, this->destination.y };
}

void Player::colliding() {
    this->velocity   = { 0.0f, 0.0f }; // TODO: are we going to use velocity ?
    this->isColliding = true;

    this->destination.x = this->position.x;
    this->destination.y = this->position.y;

}

void Player::loadTexture() {
    std::string filePath = "assets/players/textures/" + this->name + ".png";
    this->texture = LoadTexture(filePath.c_str());
}

void Player::unloadTexture() {
    UnloadTexture(this->texture);
}
