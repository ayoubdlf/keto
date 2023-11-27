#include "../include/gun.hpp"
#include "../include/game.hpp"

Gun::Gun() {
    this->available   = false;
    this->canShoot    = false;
    this->shooter     = shooter::Enemy;
    this->bulletsLeft = 0;
}

Gun::~Gun() {
    ShowCursor();
}

void Gun::useGun(shooter::type shooter) {
    this->throwGun();
    this->loadTexture();
    this->available = true;
    this->shooter = shooter;

    this->source = { 0.0f, 0.0f, (float)this->texture.width, (float)this->texture.height };
    this->scale  = 0.5f;

    /* Bullets */
    this->bulletsLeft = 0;
    if(this->shooter == shooter::Player) { this->load(MAX_BULLETS); }
    if(this->shooter == shooter::Enemy)  { this->load(MAX_BULLETS * 4); }

    if(this->shooter == shooter::Player) {
        HideCursor();
    }

}

void Gun::throwGun() {
    this->available = false;
    if(this->shooter == shooter::Player) {
        ShowCursor();
    }
}

void Gun::drawTarget() {
    Vector2 mouse = GetScreenToWorld2D(GetMousePosition(), Game::getInstance()->getCamera());
    float scale = 1.4f;
    mouse.x -= (this->target.width * scale) / 2;
    mouse.y -= (this->target.height * scale) / 2;
    DrawTextureEx(this->target, mouse, 0.0f, scale, BLACK);
}

void Gun::draw() {
    if(this->available) {
        DrawTexturePro(this->texture, this->source, this->dest, this->origin, this->rotation, WHITE);

        if(this->shooter == shooter::Player) {
            this->drawTarget();
        }

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

void Gun::updatePlayerBehaviour(Vector2 position) {
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

    // Setting a minimal distance for the shooting
    // Without this the shooter can hit himself
    this->canShoot = (Vector2Distance(this->position, mouse) > this->texture.width) ? true : false;

    this->updateBullets();
}

void Gun::updateEnemyBehaviour(Vector2 position) {
    // Making sure the gun is positioned well, near the enemy's hands
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

    // Here the target is the player position.
    // The enemy will always have the gun pointed towards the player
    Vector2 target = Game::getInstance()->getPlayer().getPosition();
    target.x += Game::getInstance()->getPlayer().getRect().width/2;
    target.y += Game::getInstance()->getPlayer().getRect().height/2;

    float angleX   = target.x - this->position.x;
    float angleY   = target.y - this->position.y;
    this->rotation = (atan2(angleY, angleX)) * RAD2DEG;

    // If the gun is pointed to the left, flip the source
    // So that when drawing, the gun will be flipped horizontally
    if(std::abs(this->rotation) > 90.0f) {
        this->origin.y = (this->source.height * this->scale) * (1-4.0f / this->source.height);
        this->source.height = -this->source.height;
    }

    this->updateBullets();
}

void Gun::update(Vector2 position) {
    if(this->available) { 
        if(this->shooter == shooter::Player) { this->updatePlayerBehaviour(position); }
        if(this->shooter == shooter::Enemy)  { this->updateEnemyBehaviour(position);  }
    }
}

void Gun::fire() {
    if(this->bulletsLeft > 0) {
        if(this->shooter == shooter::Player && this->canShoot == false) { return; }

        // Setting up bullet initial position and its projection
        float angle = this->rotation * DEG2RAD;

        Vector2 bulletPos = {
            .x = this->position.x + (std::abs(this->source.width) * this->scale * 1.8f) * cos(angle),
            .y = this->position.y + (std::abs(this->source.width) * this->scale * 1.8f) * sin(angle)
        };

        this->bullets.emplace_back();
        this->bullets.back().fire(shooter::Player, bulletPos, angle); // Firing the bullet

        this->bulletsLeft -= 1;

    }
}

void Gun::load(int bullets) {
    if(this->available) {
        this->bulletsLeft += bullets;

        if(this->shooter == shooter::Player && this->bulletsLeft > MAX_BULLETS) {
            this->bulletsLeft = MAX_BULLETS;
        }
    }
}

void Gun::loadTexture() {
    std::string path = "assets/items/pistol.png";
    this->texture = LoadTexture(path.c_str()); 

    std::string targetPath = "assets/items/target.png";
    this->target = LoadTexture(targetPath.c_str());
}

int Gun::getBulletsLeft() {
    return this->bulletsLeft;
}
