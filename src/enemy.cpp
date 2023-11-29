#include "../include/enemy.hpp"
#include "../include/game.hpp"

Enemy::Enemy() {
    this->action        = Nothing;
    this->currentFrame  = 0;
    this->framesCounter = 0;
    this->framesSpeed   = X_FRAME_SPEED; 
    this->direction     = Left;
    this->brainCounter  = 0;

    this->gun.useGun(shooter::type::Enemy);
}

void Enemy::draw() {

    /* Enemy */
    Rectangle source = this->textures[this->action].frames;
    if(this->direction == Left) { source.width = -source.width; }

    DrawTextureRec(this->textures[this->action].texture, source, this->position, WHITE);

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
    this->velocity      = {0.0f, this->velocity.y};
    this->action        = Idle;
    this->framesSpeed   = X_FRAME_SPEED;
    this->brainCounter += 1;

    Vector2 playerPos = Game::getInstance()->getPlayer().getPosition();

    int distanceToPlater = Vector2Distance(this->position, playerPos);
    if(distanceToPlater > Game::getInstance()->getPlayer().getRect().width * 10) { return; }

    // Now the distance between the enemy and the player is good
    // Now we're going to implemen the `enemy's brain`

    // 60 are FPS
    if (this->brainCounter >= 60 * 1) {
        this->brainCounter = 0;
        this->gun.fire();
    }

    // Move the enemy closer to the player
    // Leaving player.width * 2 as offset
    if(distanceToPlater <= Game::getInstance()->getPlayer().getRect().width * 2) { return; };
    if((int)this->position.y != (int)playerPos.y) { return; };

    float angleX   = playerPos.x - this->position.x;
    float angleY   = playerPos.y - this->position.y;
    float rotation = (atan2(angleY, angleX));

    this->action    = Run;
    this->direction = Right;

    this->velocity.x = (X_VELOCITY * 0.2f) * DELTA * SCALE;

    if(std::abs(rotation) * RAD2DEG > 90.0f) {
        this->velocity.x = -this->velocity.x;
        this->direction  = Left;
    }

    if((int)playerPos.x == (int)this->position.x && (int)playerPos.y == (int)this->position.y) {
        this->velocity.x = 0;
        this->action     = Idle;
    }

}

void Enemy::update() {
    this->updateBrain();
    this->updatePosition();
    this->updateFrames();

    /* Gun */
    this->gun.update(this->position);

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
    for(Tile obstacle : Game::getInstance()->getMap().getObstacles()) {
        Rectangle tile  = {obstacle.pos.x, obstacle.pos.y, (float)obstacle.texture.width, (float)obstacle.texture.height};
        Rectangle enemy = {this->position.x, this->position.y - this->velocity.y, this->width, this->height};
        
        if (CheckCollisionRecs(enemy, tile)) {
            this->velocity.x = 0;
            this->position.x = (this->position.x > tile.x) ? tile.x + this->width : tile.x - this->width;
            break;
        }
        
    }

    // Y AXIS COLLISIONS
    for(Tile obstacle : Game::getInstance()->getMap().getObstacles()) {
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

void Enemy::loadTextures() {
    std::string nothing = "assets/players/" + this->name + "/" + this->name + ".png";
    std::string idle    = "assets/players/" + this->name + "/idle.png";
    std::string run     = "assets/players/" + this->name + "/run.png";

    this->textures[Nothing] = loadCustomTexture(nothing);
    this->textures[Idle]    = loadCustomTexture(idle);
    this->textures[Run]     = loadCustomTexture(run);
}

void Enemy::reset() {
    this->~Enemy();
    new (this) Enemy();
}