#include <iostream>
#include <raylib.h>
#include "../include/weapon.hpp"

Weapon::Weapon() {
    this->type = Nothing;
}

Weapon::~Weapon() {}

void Weapon::useWeapon(Weapons weapon) {
    this->throwWeapon();
    this->type = weapon;
    this->loadTexture();
}

void Weapon::setPosition(Vector2 position) {
    this->position = position;
}

void Weapon::throwWeapon() {
    // Init all relative data to the weapon
    this->unloadTexture();
    this->type = Nothing;
    this->position = { 0.0f, 0.0f};
}

void Weapon::drawGun(Direction direction, Direction look) {
    Vector2   pos    = { this->position.x, this->position.y };
    Rectangle source = { 0.0f, 0.0f, (float)this->texture.width, (float)this->texture.height };
    Rectangle dest   = { pos.x + (this->texture.width * 0.5f), pos.y + (this->texture.height * 0.65f), (float)this->texture.width, (float)this->texture.height };
    Vector2   origin = { 2.0f, 14.0f };
    // OR Vector2   origin = { dest.width * 0.07f, dest.height * 0.47f };

    Vector2 mouse   = GetScreenToWorld2D(GetMousePosition(), CameraSingleton::getInstance()->getCamera());
    float angleX    = mouse.x - dest.x - source.x * 0.1f;
    float angleY    = mouse.y - dest.y - source.y * 0.5f;
    float rotation  = atan2(angleY, angleX) * RAD2DEG;

    if((direction || look) == Left)        { source.height = -source.height; }
    if(direction == Right && look == Left) { source.height = -source.height; }

    DrawTexturePro(this->texture, source, dest, origin, rotation, RAYWHITE);
}

void Weapon::drawSword(Direction direction, Direction look) {
    Vector2   pos    = { this->position.x, this->position.y };
    Rectangle source = { 0.0f, 0.0f, (float)this->texture.width, (float)this->texture.height };
    Rectangle dest   = { pos.x + (this->texture.width * 0.5f), pos.y + (this->texture.height * 0.65f), this->texture.width * 0.8f, this->texture.height * 0.8f };
    Vector2   origin = { 1.56f, 22.65f };
    // OR Vector2   origin = { dest.x * 0.06f, dest.y * 0.88f };

    Vector2 mouse   = GetScreenToWorld2D(GetMousePosition(), CameraSingleton::getInstance()->getCamera());
    float angleX    = mouse.x - dest.x - source.x * 0.1f;
    float angleY    = mouse.y - dest.y - source.y * 0.5f;
    float rotation  = 45 + atan2(angleY, angleX) * RAD2DEG;

    DrawTexturePro(this->texture, source, dest, origin, rotation, RAYWHITE);
}

void Weapon::draw(Direction direction, Direction look) {
    if(this->type != Nothing) {
        if(this->type == Gun)   drawGun(direction, look);
        if(this->type == Sword) drawSword(direction, look);
    }
}

void Weapon::loadTexture() {
    if(this->type != Nothing) {

        std::string weaponName;

        switch (this->type) {
            case 1: weaponName = "gun"    ; break;
            case 2: weaponName = "sword"  ; break;
            default: break;
        }

        std::string path = "assets/items/" + weaponName + ".png";
        this->texture = LoadTexture(path.c_str()); 
    }
}

void Weapon::unloadTexture() {
    if(this->type != Nothing) {
        UnloadTexture(this->texture);
    }
}
