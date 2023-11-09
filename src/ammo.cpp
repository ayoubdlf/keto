#include <iostream>
#include <raylib.h>
#include "utils.hpp"
#include "../include/ammo.hpp"

Ammo::Ammo(){}

Ammo::~Ammo(){
    this->unloadTexture();
}

void Ammo::unloadTexture() {

// If the ammo touches smthing or is out of the map limit we erease the texture

    if(this->position.x > WIDTH || this->position.y > HEIGHT) {

        UnloadTexture(this->texture);

    }else if(isThereACollision()){/* If there's a collision*/

        UnloadTexture(this->texture);

    }

}


bool Ammo::isThereACollision(){

    for (Tile obstacle : Map::getInstance()->getObstacles()) {

        Rectangle tile   = {obstacle.pos.x, obstacle.pos.y, (float)obstacle.texture.width, (float)obstacle.texture.height};
        Rectangle ammo = {this->position.x, this->position.y, this->width, this->height};
        
        if (CheckCollisionRecs(ammo, tile)) {
            
            return true;
        }
    }

     for (Tile obstacle : Map::getInstance()->getObstacles()) {
        Rectangle tile   = {obstacle.pos.x, obstacle.pos.y, (float)obstacle.texture.width, (float)obstacle.texture.height};
        Rectangle ammo = {this->position.x, this->position.y, this->width, this->height};
        
        if (CheckCollisionRecs(ammo, tile)) {
            // Head (collisions with the player head)
            return true;
        }
     }



    return false;

}