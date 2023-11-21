#include "../include/enemy.hpp"
#include "../include/game.hpp"

Enemy::Enemy() {
    this->action        = Nothing;
    this->currentFrame  = 0;
    this->framesCounter = 0;
    this->framesSpeed   = X_FRAME_SPEED; 
    this->direction     = Left;
}

void Enemy::draw() {

    /* Enemy */
    Rectangle source = this->textures[this->action].frames;
    if(this->direction == Left) { source.width = -source.width; }

    DrawTextureRec(this->textures[this->action].texture, source, this->position, RAYWHITE);

    this->drawHealthBar();

    /* Gun */
    this->gun.draw();
}

void Enemy::updateFrames() {
    this->framesCounter += 1;

    if (this->framesCounter >= (60 / this->framesSpeed)) {
        this->framesCounter = 0;
        this->currentFrame  = (this->currentFrame + 1) % int(this->textures[this->action].texture.width / this->width + 1); // (this->textures[this->action].texture.width / this->width) is the number of frames in the texture 
    }

    // Update texture X
    this->textures[this->action].frames.x = this->currentFrame * this->width;
}

void Enemy::updateBrain() {
    this->velocity    = {0.0f, this->velocity.y};
    this->action      = Idle;
    this->framesSpeed = X_FRAME_SPEED;
}

void Enemy::update() {
    this->updateBrain();
    this->updatePosition();
    this->updateFrames();

    /* Collisions */
    this->handleCollisions();

}

void Enemy::setPosition(Vector2 position) {
    this->position = position;
}

Vector2 Enemy::getPosition() {
    return this->position;
}

void Enemy::handleCollisions() {
    
    // X AXIS COLLISIONS
    for(Tile obstacle : Game::getInstance()->getObstacles()) {
        Rectangle tile  = {obstacle.pos.x, obstacle.pos.y, (float)obstacle.texture.width, (float)obstacle.texture.height};
        Rectangle enemy = {this->position.x, this->position.y - this->velocity.y, this->width, this->height};
        
        if (CheckCollisionRecs(enemy, tile)) {
            this->velocity.x = 0;
            this->position.x = (this->position.x > tile.x) ? tile.x + this->width : tile.x - this->width;
            break;
        }
        
    }

    // Y AXIS COLLISIONS
    for(Tile obstacle : Game::getInstance()->getObstacles()) {
        Rectangle tile   = {obstacle.pos.x, obstacle.pos.y, (float)obstacle.texture.width, (float)obstacle.texture.height};
        Rectangle enemy = {this->position.x, this->position.y, this->width, this->height};
        
        if (CheckCollisionRecs(enemy, tile)) {
            // Head (collisions with the enemy head)
            if (this->velocity.y < 0) {
                this->velocity.y = 0;
                this->position.y = tile.y + this->height;
            }

            // Feet (collisions with the enemy feets)
            if (this->velocity.y > 0) {
                this->velocity.y = 0;
                this->position.y = tile.y - this->height;

            }
            break;
        }
        
    }

}

ActionTexture Enemy::loadActionTexture(std::string path) {
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

void Enemy::loadTextures() {
    std::string nothing = "assets/players/" + this->name + "/" + this->name + ".png";
    std::string idle    = "assets/players/" + this->name + "/idle.png";
    std::string run     = "assets/players/" + this->name + "/run.png";

    this->textures[Nothing] = loadActionTexture(nothing);
    this->textures[Idle]    = loadActionTexture(idle);
    this->textures[Run]     = loadActionTexture(run);
}
