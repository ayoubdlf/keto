#include <iostream>
#include <raylib.h>
#include "../include/player.hpp"

Player::Player() {
    this->position      = {100.0f, 10.0f};
    this->velocity      = {0.0f, 0.0f};
    this->isJumping     = false;
    this->action        = Nothing;
    this->currentFrame  = 0;
    this->framesCounter = 0;
    this->framesSpeed   = X_FRAME_SPEED; 
    this->direction     = Right;
    this->looking       = Right;
    
    this->weapon.useWeapon(Weapons::Nothing);
}

Player::~Player() {}

float Player::getWidth() {
    return this->width;
}

float Player::getHeight() {
    return this->height;
}

void Player::setPlayer(std::string name) {
    this->name = name;
}

void Player::draw() {

    // PLAYER
    Rectangle source = this->textures[this->action].frames;
    if(this->direction == Left) { source.width = -source.width; }

    DrawTextureRec(
        this->textures[this->action].texture,
        source,
        this->position,
        RAYWHITE
    );

    /* Weapon */
    this->weapon.draw(this->direction, this->looking);
}

void Player::update() {
    this->velocity.y    += GRAVITY;
    this->position.x    += this->velocity.x;
    this->position.y    += this->velocity.y;
    this->framesCounter += 1;

    if (this->framesCounter >= (60 / this->framesSpeed)) {
        this->framesCounter = 0;
        this->currentFrame  = (this->currentFrame + 1) % int(this->textures[this->action].texture.width / this->width + 1); // (this->textures[this->action].texture.width / this->width) is the number of frames in the texture 
    }

    // Update texture X
    this->textures[this->action].frames.x = this->currentFrame * this->width;

    /* Weapon */
    this->weapon.setPosition(this->position);

    /* Collisions */
    this->handleCollisions();

}

void Player::handleInputs() {
    this->velocity    = {0.0f, this->velocity.y};
    this->action      = Idle;
    this->framesSpeed = X_FRAME_SPEED;
    Vector2 mouse     = GetScreenToWorld2D(GetMousePosition(), CameraSingleton::getInstance()->getCamera());
    this->looking     = (mouse.x >= this->position.x) ? Right : Left;
    this->direction   = this->looking;

    if(IsKeyDown(KEY_RIGHT))                  { this->velocity.x =  X_VELOCITY * DELTA * SCALE; this->action = Run;  this->direction = Right; }
    if(IsKeyDown(KEY_LEFT))                   { this->velocity.x = -X_VELOCITY * DELTA * SCALE; this->action = Run;  this->direction = Left;  }
    if(IsKeyDown(KEY_UP) && !this->isJumping) { this->velocity.y = -Y_VELOCITY * DELTA * SCALE; this->action = Jump; this->isJumping = true; this->framesSpeed = Y_FRAME_SPEED; }

    if(IsKeyDown(KEY_N)) { this->weapon.useWeapon(Weapons::Nothing); this->weapon.setPosition({ this->position.x, this->position.y }); }
    if(IsKeyDown(KEY_G)) { this->weapon.useWeapon(Weapons::Gun)    ; this->weapon.setPosition({ this->position.x, this->position.y }); }
    if(IsKeyDown(KEY_S)) { this->weapon.useWeapon(Weapons::Sword)  ; this->weapon.setPosition({ this->position.x, this->position.y }); }
}

Vector2 Player::getPosition() {
    return this->position;
}

Vector2 Player::getVelocity() {
    return this->velocity;
}

void Player::handleCollisions() {
    
    // X AXIS COLLISIONS
    for(Tile obstacle : Map::getInstance()->getObstacles()) {
        Rectangle tile   = {obstacle.pos.x, obstacle.pos.y, (float)obstacle.texture.width, (float)obstacle.texture.height};
        Rectangle player = {this->position.x, this->position.y - this->velocity.y, this->width, this->height};
        
        if (CheckCollisionRecs(player, tile)) {
            this->velocity.x = 0;
            this->position.x = (this->position.x > tile.x) ? tile.x + this->width : tile.x - this->width;
            break;
        }
        
    }

    // Y AXIS COLLISIONS
    for(Tile obstacle : Map::getInstance()->getObstacles()) {
        Rectangle tile   = {obstacle.pos.x, obstacle.pos.y, (float)obstacle.texture.width, (float)obstacle.texture.height};
        Rectangle player = {this->position.x, this->position.y, this->width, this->height};
        
        if (CheckCollisionRecs(player, tile)) {
            // Head (collisions with the player head)
            if (this->velocity.y < 0) {
                this->velocity.y = 0;
                this->position.y = tile.y + this->height;
            }

            // Feet (collisions with the player feets)
            if (this->velocity.y > 0) {
                this->velocity.y = 0;
                this->position.y = tile.y - this->height;
                this->isJumping = false;
            }
            break;
        }
        
    }

}

ActionTexture Player::loadActionTexture(std::string path) {
    Texture2D texture = LoadTexture(path.c_str());

    if(strstr(path.c_str(), this->name.c_str())) {
        this->width  =  this->textures[Nothing].texture.width;
        this->height =  this->textures[Nothing].texture.height;
    }

    return {
        .texture = texture,
        .frames  = {
            0.0f,
            0.0f,
            this->width,
            this->height
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
    this->textures[Nothing] = loadActionTexture(nothing);
    this->textures[Idle]    = loadActionTexture(idle);
    this->textures[Run]     = loadActionTexture(run);
    this->textures[Jump]    = loadActionTexture(jump);
}
