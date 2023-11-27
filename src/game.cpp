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

    // Init map
    this->map.load("assets/map/map.txt");
    
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

    // Init enemies
    for (int i = 0; i < NB_ENEMIES; i++) {
        this->enemies.emplace_back();
        this->enemies[i].setName("keti");
        this->enemies[i].setPosition({ 256.0f, 10.0f });
    }

    // Load textures
    this->loadTextures();

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

std::vector<Tile>& Game::getObstacles() {
    return this->map.getObstacles();
}

Player& Game::getPlayer() {
    return this->player;
}

std::vector<Enemy>& Game::getEnemies() {
    return this->enemies;
}

void Game::update() {
    this->updateCamera();

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

void Game::draw() {
    BeginMode2D(this->fixedCamera);
        this->player.drawStats();
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

    EndMode2D();
}

void Game::loadTextures() {
    this->map.loadTextures();
    this->player.loadTextures();

    for (int i = 0; i < (int)this->enemies.size(); i++) {
        if(this->enemies[i].isAlive()) {
            this->enemies[i].loadTextures();
        }
    } 
}
