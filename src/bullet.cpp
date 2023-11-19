#include <iostream>
#include <raylib.h>
#include "../include/bullet.hpp"
#include "../include/map.hpp"

Bullet::Bullet() {
    this->scale = 0.4f;
}

Bullet::~Bullet() {}

void Bullet::draw() {
    DrawTextureEx(this->texture, this->position, this->rotation, this->scale, RAYWHITE);
}

void Bullet::update() {
    this->position.x += BULLET_VELOCITY * cos(this->angle);
    this->position.y += BULLET_VELOCITY * sin(this->angle);
    
    this->handleCollision();
}

void Bullet::fire(Vector2 position, float angle) {
    this->loadTexture();
    this->active   = true;
    this->position = position;
    this->rotation = std::abs(angle) * RAD2DEG;
    this->angle    = angle;
}

void Bullet::handleCollision() {
    for(Tile obstacle : Map::getInstance()->getObstacles()) {
        Rectangle tile   = {obstacle.pos.x, obstacle.pos.y, (float)obstacle.texture.width, (float)obstacle.texture.height};
        Rectangle bullet = {this->position.x, this->position.y, (float)this->texture.width * this->scale, (float)this->texture.height * this->scale};
        
        if (CheckCollisionRecs(bullet, tile)) {
            this->active = false;
            break;
        }
        
    }
}

bool Bullet::isActive() {
    return this->active;
}

void Bullet::loadTexture() {
    std::string path = "assets/items/bullet.png";
    this->texture = LoadTexture(path.c_str()); 
}
