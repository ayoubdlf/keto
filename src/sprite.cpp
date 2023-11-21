#include "../include/sprite.hpp"

Sprite::Sprite() {
    this->position = {100.0f, 10.0f};
    this->velocity = {0.0f, 0.0f};
    this->health   = 0;

    this->heal(MAX_HEALTH);
}

Sprite::~Sprite() {}

void Sprite::setName(std::string name) {
    this->name = name;
}

Rectangle Sprite::getRect() {
    return {
        .x      = this->position.x,
        .y      = this->position.y,
        .width  = this->width,
        .height = this->height
    };
}

void Sprite::heal(int health) {
    if(this->health < 10) {
        this->health += health;
    }
}

int Sprite::getHealth() {    
    return this->health;
}

bool Sprite::isAlive() {
    return this->health > 0;
}

void Sprite::damage(int damage) {
    this->health -= damage;
}

Vector2 Sprite::getPosition() {
    return this->position;
}

void Sprite::updatePosition() {
    this->velocity.y += GRAVITY;
    this->position.x += this->velocity.x;
    this->position.y += this->velocity.y;
}

void Sprite::drawHealthBar() {
    float factor = ((float)this->health / (float)MAX_HEALTH);
    float posx   = this->position.x + (this->width * 0.15); // To make the bar more centered
    float posy   = this->position.y - 2;

    DrawRectangleLinesEx({posx, posy, float(this->width * 0.75), 5}, 0.5f, BLACK);
    DrawRectangle(posx, posy, (this->width * 0.8) * factor, 5, RED);
}