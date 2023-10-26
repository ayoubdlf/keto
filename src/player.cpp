#include <iostream>
#include <raylib.h>
#include "../include/player.hpp"

Player::Player() {
    this->position      = {0.0f, 0.0f};
    this->velocity      = {0.0f, 0.0f};
    this->isJumping     = false;
    this->action        = Action::Nothing;
    this->currentFrame  = 0;
    this->framesCounter = 0;
    this->framesSpeed   = X_FRAME_SPEED; 
    this->direction     = "Right";
}

Player::~Player() {
    this->unloadTextures();
}

void Player::setPlayer(std::string name) {
    this->name = name;
}

void Player::draw() {
    Rectangle source = this->textures[this->action].frames;
    if(this->direction == "Left") { source.width = -source.width; }

    DrawTextureRec(
        this->textures[this->action].texture,
        source,
        this->position,
        RAYWHITE
    );
    
}

void Player::update() {
    this->velocity.y    += GRAVITY;
    this->position.x    += this->velocity.x;
    this->position.y    += this->velocity.y;
    this->framesCounter += 1; 

    if (this->framesCounter >= (60 / this->framesSpeed)) {
        this->framesCounter = 0;
        this->currentFrame  = (this->currentFrame + 1) % (this->textures[this->action].texture.width / TILE_SIZE + 1); // (this->textures[this->action].texture.width / TILE_SIZE) is the number of frames in the texture 
    }

    // Update texture X
    this->textures[this->action].frames.x = this->currentFrame * TILE_SIZE;
}

void Player::handleInputs() {
    this->velocity    = {0.0f, this->velocity.y};
    this->action      = Action::Idle;
    this->framesSpeed = X_FRAME_SPEED;

    if(IsKeyDown(KEY_RIGHT))                  { this->velocity.x =  X_VELOCITY * DELTA * SCALE; this->action = ::Action::Run;  this->direction = "Right"; }
    if(IsKeyDown(KEY_LEFT))                   { this->velocity.x = -X_VELOCITY * DELTA * SCALE; this->action = ::Action::Run;  this->direction = "Left";  }
    if(IsKeyDown(KEY_UP) && !this->isJumping) { this->velocity.y = -Y_VELOCITY * DELTA * SCALE; this->action = ::Action::Jump; this->isJumping = true; this->framesSpeed = Y_FRAME_SPEED; }

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

PlayerTexture Player::loadPlayerTexture(std::string path) {
    Texture2D texture = LoadTexture(path.c_str());
    
    return {
        .texture = texture,
        .frames  = {
            0.0f,
            0.0f,
            TILE_SIZE,
            TILE_SIZE
        }
    };

}

void Player::loadTextures() {

    // TODO: create a function that handles all of that
    std::string nothing = "assets/players/" + this->name + "/" + this->name + ".png";
    std::string idle    = "assets/players/" + this->name + "/idle.png";
    std::string run     = "assets/players/" + this->name + "/run.png";
    std::string jump    = "assets/players/" + this->name + "/jump.png";

    // TODO: I think there is another easy implementatin of that
    textures[::Action::Nothing] = loadPlayerTexture(nothing);
    textures[::Action::Idle]    = loadPlayerTexture(idle);
    textures[::Action::Run]     = loadPlayerTexture(run);
    textures[::Action::Jump]    = loadPlayerTexture(jump);
}

void Player::unloadTextures() {
    for(PlayerTexture playerTexture : this->textures) {
        UnloadTexture(playerTexture.texture);
    }
}
