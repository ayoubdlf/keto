#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include "../include/game.hpp"
#include "../include/camera.hpp"

Game::Game(int width, int height) {

    // Init window
    SetTraceLogLevel(LOG_WARNING); // remove annoying logging
    SetConfigFlags(FLAG_WINDOW_HIGHDPI); // DPI
    InitWindow(width, height, "Keto");
    SetTargetFPS(60);

    // Init player
    this->player.setPlayer();

    // Init map
    Map::getInstance()->load("assets/map/map.txt");

    // Init camera
    CameraSingleton::getInstance()->getCamera().offset   = { width/2.0f, height/2.0f };
    CameraSingleton::getInstance()->getCamera().zoom     = ZOOM;
    CameraSingleton::getInstance()->getCamera().rotation = 0.0f;
}

Game::~Game() {}

void Game::input() {
    this->player.handleInputs();
}

void Game::updateCamera() {

    // Old version :
    // CameraSingleton::getInstance()->getCamera().target = this->player.getPosition();
   
    // New Smoother one :
    float minSpeed        = 80;
    float minEffectLength = 20;
    float fractionSpeed   = Y_VELOCITY;

    CameraSingleton::getInstance()->getCamera().offset = { WIDTH/2.0f, HEIGHT/2.0f };
    Vector2 diff  = Vector2Subtract(this->player.getPosition(), CameraSingleton::getInstance()->getCamera().target);
    float length  = Vector2Length(diff);

    if (length > minEffectLength) {
        float speed = fmaxf(fractionSpeed * length, minSpeed);
        CameraSingleton::getInstance()->getCamera().target = Vector2Add(CameraSingleton::getInstance()->getCamera().target, Vector2Scale(diff, speed*DELTA/length));
    }
}

void Game::update() {
    this->updateCamera();
    this->player.update();
}

void Game::render() {
    BeginDrawing();

        ClearBackground(RAYWHITE);
        this->draw();
    
    EndDrawing();
}

void Game::draw() {
    BeginMode2D(CameraSingleton::getInstance()->getCamera());
        Map::getInstance()->draw();
        this->player.draw();
    EndMode2D();
}

void Game::loadTextures() {
    Map::getInstance()->loadTextures();
    this->player.loadTextures();
}
