#include "../include/bullet.hpp"
#include "../include/map.hpp"
#include "../include/game.hpp"

Bullet::Bullet() {
    this->scale = 0.4f;
}

Bullet::~Bullet() {}

void Bullet::draw() {
    DrawTextureEx(this->texture, this->position, this->rotation, this->scale, WHITE);
}

void Bullet::update() {
    this->position.x += BULLET_VELOCITY * cos(this->angle);
    this->position.y += BULLET_VELOCITY * sin(this->angle);
    
    this->handleCollision();
}

void Bullet::fire(shooter::type shooter,  Vector2 position, float angle) {
    this->loadTexture();
    this->active   = true;
    this->shooter  = shooter;
    this->position = position;
    this->rotation = std::abs(angle) * RAD2DEG;
    this->angle    = angle;
}

void Bullet::handleCollision() {
    Rectangle bullet = {this->position.x, this->position.y, (float)this->texture.width * this->scale, (float)this->texture.height * this->scale};
    
    /* Collision with tiles */
    for(Tile obstacle : Game::getInstance()->getMap().getObstacles()) {
        Rectangle tile   = { obstacle.pos.x, obstacle.pos.y, (float)obstacle.texture.width, (float)obstacle.texture.height };

        if (CheckCollisionRecs(bullet, tile)) {
            this->active = false;
            return;
        }

    }

    /* Check if the bullet hit the player or one of the enemies */
    Rectangle player            = Game::getInstance()->getPlayer().getRect();
    std::vector<Enemy>& enemies = Game::getInstance()->getEnemies();
    
    // Check if the bullet hit the player
    if (CheckCollisionRecs(bullet, player)) {
        this->active = false;
        Game::getInstance()->getPlayer().damage(1);
        return;
    }

    // Check if the bullet hit the one of the enemies
    for (int i = 0; i < (int)enemies.size(); i++) {
        if (CheckCollisionRecs(bullet, enemies[i].getRect())) {
            this->active = false;
            enemies[i].damage(1);
            if(enemies[i].getHealth() <= 0) {
                Game::getInstance()->getPlayer().kill();
            }
            return;
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
