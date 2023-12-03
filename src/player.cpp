#include "../include/player.hpp"
#include "../include/game.hpp"

Player::Player() {
    this->name          = "keto";
    this->position      = {100.0f, 10.0f};
    this->kills         = 0;
    this->coins         = 0;
    this->isJumping     = false;
    this->action        = Nothing;
    this->currentFrame  = 0;
    this->framesCounter = 0;
    this->framesSpeed   = X_FRAME_SPEED; 
    this->direction     = Right;

}

void Player::useGun() {
    this->gun.useGun(shooter::type::Player);
}

void Player::drawTag() {
    int posx = this->position.x + (this->width/2) - (this->tagTexture.width/2);
    int posy = this->position.y - 5;
    DrawTexture(this->tagTexture, posx, posy, WHITE);
}

void Player::drawHealthBar() {
    float scale = 1.6f;
    Vector2 pos = { 5.0f, 8.0f };
    
    DrawTextureEx(this->healthBarTexture.left, { pos.x, pos.y }, 0.0f, scale, WHITE);
    pos.x += this->healthBarTexture.left.width * scale;

    for (int i = 1; i < MAX_HEALTH + 1; i++) {
        DrawTextureEx((this->health >= i) ? this->healthBarTexture.middle : this->healthBarTexture.middle_empty, { pos.x, pos.y }, 0.0f, scale, WHITE);
        pos.x += this->healthBarTexture.middle.width * scale;
    }

    DrawTextureEx(this->healthBarTexture.right, { pos.x, pos.y }, 0.0f, scale, WHITE);
    DrawTextureEx(this->healthBarTexture.hp_logo, { (this->healthBarTexture.middle.width * scale)*1.5f, 2.0f }, 0.0f, scale, WHITE);
}

void Player::drawNumbers(Vector2 position, Texture2D texture, int value) {
    std::string bullets  = std::to_string(value);
    
    Vector2 offset = {
        .x = texture.width  * 0.4f,
        .y = texture.height * 0.15f
    };

    for (int i = 0; i < (int)bullets.size(); i++) {
        int index = bullets[i] - '0';
        DrawTextureEx(this->numbersTexture[index], { position.x + offset.x, position.y + offset.y }, 0.0f, 1.0f, WHITE);
        offset.x = offset.x + this->numbersTexture[index].width * 1.1f;
    }
}

void Player::drawKills() {
    Vector2 position = { 5.0f, 30.0f };

    DrawTextureEx(this->killsTexture, position, 0.0f, 1.0f, WHITE);
    this->drawNumbers(position, this->killsTexture, this->kills);
}

void Player::drawBullets() {
    Vector2 position = { 50.0f, 30.0f };

    DrawTextureEx(this->bulletsTexture, position, 0.0f, 1.0f, WHITE);
    this->drawNumbers(position, this->bulletsTexture, this->gun.getBulletsLeft());
}

void Player::drawCoins() {
    Vector2 position = { 5.0f, 52.0f };

    DrawTextureEx(this->coinsTexture, position, 0.0f, 1.0f, WHITE);
    this->drawNumbers(position, this->coinsTexture, this->coins);
}

void Player::drawStats() {
    this->drawHealthBar();
    this->drawKills();
    this->drawBullets();
    this->drawCoins();
}

void Player::draw() {

    /* Player */
    Rectangle source = this->textures[this->action].frames;
    if(this->direction == Left) { source.width = -source.width; }

    DrawTextureRec(this->textures[this->action].texture, source, this->position, WHITE);
    this->drawTag();

    /* Gun */
    this->gun.draw();
}

void Player::updateFrames() {
    this->framesCounter += 1;

    if (this->framesCounter >= (60 / this->framesSpeed)) {
        this->framesCounter = 0;
        this->currentFrame  = (this->currentFrame + 1) % int(this->textures[this->action].texture.width / this->width + 1); // (this->textures[this->action].texture.width / this->width) is the number of frames in the texture 
    }

    // Update texture X
    this->textures[this->action].frames.x = this->currentFrame * this->width;
}

void Player::update() {
    this->updatePosition();
    this->updateFrames();

    /* Gun */
    this->gun.update(this->position);

    /* Collisions */
    this->handleCollisions();

}

void Player::handleInputs() {
    this->velocity    = { 0.0f, this->velocity.y };
    this->action      = Idle;
    this->framesSpeed = X_FRAME_SPEED;
    Vector2 mouse     = GetScreenToWorld2D(GetMousePosition(), Game::getInstance()->getCamera());
    this->direction   = (mouse.x >= this->position.x) ? Right : Left;

    if(IsKeyDown(KEY_RIGHT))                  { this->velocity.x =  X_VELOCITY * DELTA * SCALE; this->action = Run;  this->direction = Right; }
    if(IsKeyDown(KEY_LEFT))                   { this->velocity.x = -X_VELOCITY * DELTA * SCALE; this->action = Run;  this->direction = Left;  }
    if(IsKeyDown(KEY_UP) && !this->isJumping) { this->velocity.y = -Y_VELOCITY * DELTA * SCALE; this->action = Jump; this->isJumping = true; this->framesSpeed = Y_FRAME_SPEED; }

    // TODO: add save icon tho'
    if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S)) {
        Game::getInstance()->save();
        Game::getInstance()->alert("SAVED");
    }

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) { this->gun.fire(); }
    
}

Vector2 Player::getPosition() {
    return this->position;
}

void Player::handleCollisions() {
    
    // PLAYER OUTSIDE MAP
    // if((this->position.x + this->width) < 0 || this->position.x > Game::getInstance()->getMap().getWidth() || (this->position.y + this->height) < 0 || this->position.y > Game::getInstance()->getMap().getHeight())
    if(this->position.y - this->height * 6 > Game::getInstance()->getMap().getHeight()) {
        this->health = 0;
    }

    // X AXIS COLLISIONS
    for(Tile obstacle : Game::getInstance()->getMap().getObstacles()) {
        Rectangle tile   = {obstacle.pos.x, obstacle.pos.y, (float)obstacle.texture.width, (float)obstacle.texture.height};
        Rectangle player = {this->position.x, this->position.y - this->velocity.y, this->width, this->height};
        
        if (CheckCollisionRecs(player, tile)) {
            this->velocity.x = 0;
            this->position.x = (this->position.x > tile.x) ? tile.x + this->width : tile.x - this->width;
            break;
        }
        
    }

    // Y AXIS COLLISIONS
    for(Tile obstacle : Game::getInstance()->getMap().getObstacles()) {
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
    
    Rectangle playerX = {this->position.x, this->position.y - this->velocity.y, this->width, this->height};
    Rectangle playerY = {this->position.x, this->position.y, this->width, this->height};
    Tile checkPoint = Game::getInstance()->getMap().getCheckPoint();
    Rectangle checkPointRect = {checkPoint.pos.x, checkPoint.pos.y, (float)checkPoint.texture.width, (float)checkPoint.texture.height};

    // COLLISION WITH THE CHECKPOINT
    if (CheckCollisionRecs(playerX, checkPointRect) || CheckCollisionRecs(playerY, checkPointRect)) {
        if(Game::getInstance()->getLevels().isLastLevel()) {
            Game::getInstance()->getMenu().setState(Completed);
        } else {
            Game::getInstance()->nextLevel();
        }
        return;
    }

    // POWER UPS COLLISION
    std::vector<Tile> powerUps = Game::getInstance()->getMap().getPowerUps();

    for (int i = 0; i < (int)powerUps.size(); i++) {
        Rectangle powerUp   = {powerUps[i].pos.x, powerUps[i].pos.y, (float)powerUps[i].frames.width, (float)powerUps[i].frames.height};
        
        if (CheckCollisionRecs(playerX, powerUp)) {
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<int> dist(PowerUp_Bullet, PowerUp_MedKit); // [2-5]
            
            switch (powerUps[i].type) {
                case PowerUp_Bullet   : this->gun.load(5)     ; Game::getInstance()->alert("+5 bullets") ; break;
                case PowerUp_Coin     : this->coins += 1      ; Game::getInstance()->alert("+1 coin")    ; break;
                case PowerUp_Heart    : this->heal(1)         ; Game::getInstance()->alert("+1 heart")   ; break;
                case PowerUp_MedKit   : this->heal(MAX_HEALTH); Game::getInstance()->alert("FULL HEALTH"); break;
                case PowerUp_LuckyBox :
                    switch (dist(mt)) {
                        case PowerUp_Bullet   : this->gun.load(10)    ; Game::getInstance()->alert("+10 bullets"); break;
                        case PowerUp_Coin     : this->coins += 10     ; Game::getInstance()->alert("+10 coins")  ; break;
                        case PowerUp_Heart    : this->heal(5)         ; Game::getInstance()->alert("+5 hearts")  ; break;
                        case PowerUp_MedKit   : this->heal(MAX_HEALTH); Game::getInstance()->alert("FULL HEALTH"); break;
                        default: break;
                    }            
                default: break;
            }
            
            Game::getInstance()->getMap().usePowerUp(i);
            break;
        }
    }
}

void Player::kill() {
    this->kills += 1;
}

stats Player::getStats() {
    return {
        this->health,
        this->kills,
        this->gun.getBulletsLeft(), // bulletsLeft
        this->coins,
    };
}

void Player::loadData(json data) {
    this->name       = data["name"];
    this->health     = data["hp"].get<int>();
    this->kills      = data["kills"].get<int>();
    this->coins      = data["coins"].get<int>();
    this->position.x = data["position"]["x"].get<int>();
    this->position.y = data["position"]["y"].get<int>();
    this->loadTextures();

    this->gun.loadData(data);
}

void Player::loadTextures() {
    /* Actions */
    std::string nothing     = "assets/players/" + this->name + "/" + this->name + ".png";
    std::string idle        = "assets/players/" + this->name + "/idle.png";
    std::string run         = "assets/players/" + this->name + "/run.png";
    std::string jump        = "assets/players/" + this->name + "/jump.png";

    this->textures[Nothing] = loadCustomTexture(nothing);
    this->textures[Idle]    = loadCustomTexture(idle);
    this->textures[Run]     = loadCustomTexture(run);
    this->textures[Jump]    = loadCustomTexture(jump);
    this->textures[Jump]    = loadCustomTexture(jump);

    /* Tag */
    std::string tag_path = "assets/items/tag.png";
    this->tagTexture     = LoadTexture(tag_path.c_str());

    /* Health Bar */
    std::string health_left         = "assets/items/stats/healthBar/left.png";
    std::string health_middle       = "assets/items/stats/healthBar/middle.png";
    std::string health_middle_empty = "assets/items/stats/healthBar/middle_empty.png";
    std::string health_right        = "assets/items/stats/healthBar/right.png";
    std::string hp_logo             = "assets/items/stats/healthBar/hp_logo.png";

    this->healthBarTexture.left          = LoadTexture(health_left.c_str());
    this->healthBarTexture.middle        = LoadTexture(health_middle.c_str());
    this->healthBarTexture.middle_empty  = LoadTexture(health_middle_empty.c_str());
    this->healthBarTexture.right         = LoadTexture(health_right.c_str());
    this->healthBarTexture.hp_logo       = LoadTexture(hp_logo.c_str());

    /* Kills */
    std::string kills_path = "assets/items/stats/kills.png";
    this->killsTexture     = LoadTexture(kills_path.c_str());

    /* Bullets */
    std::string bullets_path = "assets/items/stats/bullets.png";
    this->bulletsTexture     = LoadTexture(bullets_path.c_str());

    /* Numbers */
    std::string coins_path = "assets/items/stats/coins.png";
    this->coinsTexture     = LoadTexture(coins_path.c_str());

    /* Numbers */
    for (int i = 0; i < 10; i++) {
        std::string number_path = "assets/items/stats/numbers/" + std::to_string(i) + ".png";
        this->numbersTexture[i] = LoadTexture(number_path.c_str()); 
    }
    
}

void Player::reset() {
    this->~Player();
    new (this) Player();
}