#include "../include/gun.hpp"
#include "../include/game.hpp"

Gun::Gun() {
    this->available = false;
}

Gun::~Gun() {}

void Gun::useGun() {
    this->throwGun();
    this->loadTexture();
    this->available = true;

    this->source = { 0.0f, 0.0f, (float)this->texture.width, (float)this->texture.height };
    this->scale  = 0.5f;
    
    /* Bullets */
    this->nbBullets = 0;
    this->load(MAX_BULLETS);

}

void Gun::throwGun() {
    this->available = false;
}

void Gun::draw() {
    if(this->available) {
        DrawTexturePro(this->texture, this->source, this->dest, this->origin, this->rotation, RAYWHITE);

        /* Bullets */
        for (Bullet bullet : this->bullets) {
            bullet.draw();
        }
    }
}

void Gun::updateBullets() {
    /* Bullets */
    for (int i = 0; i < (int)this->bullets.size(); i++) {
        this->bullets[i].update();
        
        // If the bullet colllided with a tile, remove it.
        if(!this->bullets[i].isActive()) {
            this->bullets.erase(this->bullets.begin() + i);
        }
    }
}

void Gun::update(Vector2 position) {
    if(this->available) {
    
        // Making sure the gun is positioned well, near the player hands
        this->position.x    = position.x + 16.0f;
        this->position.y    = position.y + 22.0f;

        this->source.height = std::abs(this->source.height);
        this->dest   = {
            .x      = this->position.x,
            .y      = this->position.y,
            .width  = (this->source.width * this->scale),
            .height = (this->source.height * this->scale)
        };
        this->origin = {
            .x = (this->source.width  * this->scale) * (0.0f / this->source.width),
            .y = (this->source.height * this->scale) * (4.0f / this->source.height)
        };

        Vector2 mouse  =  GetScreenToWorld2D(GetMousePosition(), Game::getInstance()->getCamera());
        float angleX   = mouse.x - this->position.x;
        float angleY   = mouse.y - this->position.y;
        this->rotation = (atan2(angleY, angleX)) * RAD2DEG;

        // If the gun is pointed to the left, flip the source
        // So that when drawing, the gun will be flipped horizontally
        if(std::abs(this->rotation) > 90.0f) {
            this->origin.y = (this->source.height * this->scale) * (1-4.0f / this->source.height);
            this->source.height = -this->source.height;
        }

        this->updateBullets();
    }
}

void Gun::fire() {
    if(this->nbBullets > 0) {

        // Setting up bullet initial position and its projection
        float angle = this->rotation * DEG2RAD;

        Vector2 bulletPos = {
            .x = this->position.x + (std::abs(this->source.width) * this->scale) * cos(angle),
            .y = this->position.y + (std::abs(this->source.width) * this->scale) * sin(angle)
        };

        this->bullets.emplace_back();
        this->bullets.back().fire(bulletPos, angle); // Firing the bullet

        this->nbBullets -= 1;
    }
}

void Gun::load(int bullets) {
    if(this->available) {
        this->nbBullets += bullets;

        if(this->nbBullets > MAX_BULLETS) {
            this->nbBullets = MAX_BULLETS;
        }
    }
}

void Gun::loadTexture() {
    // std::string path = "assets/items/gun.png";
    std::string path = "assets/items/pistol.png";
    this->texture = LoadTexture(path.c_str()); 
}
