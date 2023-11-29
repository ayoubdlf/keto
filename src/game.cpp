#include "../include/game.hpp"

Game* Game::instance = 0;

Game* Game::getInstance() {
    if (instance == 0) { instance = new Game(WIDTH, HEIGHT); }
    return instance;
}


Game::Game(int width, int height) {

    // Init window
    SetTraceLogLevel(LOG_WARNING);         // remove annoying logging
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);   // DPI
    SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Make resizing window possible

    InitWindow(width, height, "Keto");
    SetTargetFPS(60);
    SetTextureFilter(GetFontDefault().texture, TEXTURE_FILTER_POINT);

    // Setting alerts to false
    this->alertMessage.active = false;

    // Init levels
    this->levels.create();

    // Init map
    this->map.load(this->levels.getCurrentLevelPath());
    
    // Init main camera
    this->camera.target   = { width/2.0f, height/2.0f };
    this->camera.offset   = { width/2.0f, height/2.0f };
    this->camera.zoom     = ZOOM;
    this->camera.rotation = 0.0f;

    // Init foreground camera (player stats, menu)
    this->fixedCamera.target   = { 0 };
    this->fixedCamera.offset   = { 0 };
    this->fixedCamera.zoom     = ZOOM;
    this->fixedCamera.rotation = 0.0f;


    // Init player
    this->player.setName();
    this->player.useGun();

    // Init enemies
    for (int i = 0; i < NB_ENEMIES; i++) {
        this->enemies.emplace_back();
        this->enemies[i].setName("keti");
        this->enemies[i].setPosition({ 256.0f, 10.0f });
    }

    // Load textures
    this->loadTextures();

    HideCursor();

}

Game::~Game() {}

void Game::init() {
    /*  This method does nothing. But it's helpful in the main.cpp
        Calling this function before the game loop,
        will allow us to initialize out instance of the game singleton.
    */
}

void Game::input() {
    if(this->player.isAlive()) {
        this->player.handleInputs();
    }
}

void Game::updateCamera() {
    float minSpeed        = 80;
    float minEffectLength = 20;
    float fractionSpeed   = Y_VELOCITY;

    this->camera.offset = { GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
    
    Vector2 diff  = Vector2Subtract(this->player.getPosition(), this->camera.target);
    float length  = Vector2Length(diff);


    if (length > minEffectLength) {
        float speed = fmaxf(fractionSpeed * length, minSpeed);
        this->camera.target = Vector2Add(this->camera.target, Vector2Scale(diff, speed*DELTA/length));
    }
}

Camera2D Game::getCamera() {
    return this->camera;
}

Map& Game::getMap() {
    return this->map;
}

Player& Game::getPlayer() {
    return this->player;
}

Levels& Game::getLevels() {
    return this->levels;
}

void Game::alert(std::string message) {
    this->alertMessage.message  = message;
    this->alertMessage.position = { this->player.getPosition().x, this->player.getPosition().y - this->player.getRect().height * 0.2f };
    this->alertMessage.time     = 45;
    this->alertMessage.active   = true;
}

std::vector<Enemy>& Game::getEnemies() {
    return this->enemies;
}

void Game::update() {
    this->updateCamera();
    this->map.update();

    if(this->player.isAlive()) {
        this->player.update();

        for (int i = 0; i < (int)this->enemies.size(); i++) {
            if(this->enemies[i].isAlive()) {
                this->enemies[i].update();
            } else {
                // Deleting the killed enemy from the vector
                this->enemies.erase(this->enemies.begin() + i);
            }
        }
    }
}

void Game::render() {
    BeginDrawing();

        ClearBackground(WHITE);
        this->draw();
    
    EndDrawing();
}

void Game::drawTarget() {
    Vector2 mouse = GetScreenToWorld2D(GetMousePosition(), Game::getInstance()->getCamera());
    float scale = 1.4f;
    
    mouse.x -= (this->target.width * scale) / 2;
    mouse.y -= (this->target.height * scale) / 2;

    DrawTextureEx(this->target, mouse, 0.0f, scale, BLACK);
}

void Game::drawLevelNumber() {
    std::string level  = std::to_string(this->levels.getCurrentLevel());
    Vector2 screenSize = GetScreenToWorld2D({ (float)GetScreenWidth(), (float)GetScreenHeight() }, this->fixedCamera);
    int fontSize       = 30.0f;
    DrawTextEx(GetFontDefault(), level.c_str(), { screenSize.x/2.0f - MeasureText(level.c_str(), fontSize), 20.0f }, fontSize, 1.0f, BLACK);
}

void Game::draw() {
    BeginMode2D(this->fixedCamera);
        this->player.drawStats();
        this->drawLevelNumber();    
    EndMode2D();

    BeginMode2D(this->camera);
        
        this->map.draw();

        for (int i = 0; i < (int)this->enemies.size(); i++) {
            if(this->enemies[i].isAlive()) {
                this->enemies[i].draw();
            }
        }

        if(this->player.isAlive()) {
            this->player.draw();
        }

        // Show the alert message right on top of the player
        if(this->alertMessage.active) {
            int textMiddle = (MeasureText(this->alertMessage.message.c_str(), 10.0f))/2;
            DrawTextEx(GetFontDefault(), this->alertMessage.message.c_str(), this->alertMessage.position, 10.0f, 1.0f, BLACK);
            this->alertMessage.position = { this->player.getRect().x + this->player.getRect().width/2 - textMiddle, this->alertMessage.position.y - 0.5f };
            this->alertMessage.time    -= 1;
            this->alertMessage.active   = (this->alertMessage.time != 0);
        }

        // Draw our custom cursor
        this->drawTarget();
    EndMode2D();
}

void Game::load() {
    std::ifstream file("data.json");
    
    if (file.is_open()) {
        json data;
        file >> data;

        if(this->levels.getCurrentLevel() != data["level"].get<int>()) {
            this->levels.load(data["level"].get<int>());
            
            this->map.reset();
            this->player.reset();
            this->enemies.clear();
            this->enemies.shrink_to_fit();

            this->map.load(this->levels.getCurrentLevelPath());
            this->player.setName();
            this->player.useGun();

            this->loadTextures();
        } else {
            this->levels.load(data["level"].get<int>());
        }

        this->player.loadData(data);
    }

    file.close();
}

void Game::save() {

    json data = {
        /* Game */
        { "level"   , this->levels.getCurrentLevel() },
        /* Player */
        { "name"    , this->player.getName() },
        { "hp"      , this->player.getStats().health },
        { "kills"   , this->player.getStats().kills },
        { "bullets" , this->player.getStats().bullets  },
        { "coins"   , this->player.getStats().coins  },
        { "position", {
            { "x", this->player.getPosition().x },
            { "y", this->player.getPosition().y },
        }}
    };

    std::ofstream file("data.json");

    if (file.is_open()) {
        file << data.dump();
    }

    file.close();

}

void Game::nextLevel() {
    this->levels.nextLevel();

    this->map.reset();
    this->player.reset();
    this->enemies.clear();
    this->enemies.shrink_to_fit();

    this->map.load(this->levels.getCurrentLevelPath());
    this->player.setName();
    this->player.useGun();

    this->loadTextures();
}

void Game::loadTextures() {
    this->map.loadTextures();
    this->player.loadTextures();

    for (int i = 0; i < (int)this->enemies.size(); i++) {
        if(this->enemies[i].isAlive()) {
            this->enemies[i].loadTextures();
        }
    } 

    std::string targetPath = "assets/items/target.png";
    this->target = LoadTexture(targetPath.c_str());
}
