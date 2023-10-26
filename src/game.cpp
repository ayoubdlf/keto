#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include "../include/game.hpp"

Game::Game(int width, int height) {

    // Init window
    SetTraceLogLevel(LOG_WARNING); // remove annoying logging
    SetConfigFlags(FLAG_WINDOW_HIGHDPI); // DPI
    InitWindow(width, height, "Keto");
    SetTargetFPS(60);

    // Init player
    this->player.setPlayer();

    // Init map
    this->map.load("assets/map/map.txt");

    this->camera.offset = { width/2.0f, height/2.0f };
    this->camera.zoom = ZOOM;
    this->camera.rotation = 0.0f;
}

Game::~Game() {}

void Game::input() {
    this->player.handleInputs();
}

void Game::updateCamera() {

    // Old version :
    // this->camera.target = this->player.getPosition();
   
    // New Smoother one :
    float minSpeed        = 80;
    float minEffectLength = 20;
    float fractionSpeed   = Y_VELOCITY;

    this->camera.offset = { WIDTH/2.0f, HEIGHT/2.0f };
    Vector2 diff        = Vector2Subtract(this->player.getPosition(), this->camera.target);
    float length        = Vector2Length(diff);

    if (length > minEffectLength) {
        float speed = fmaxf(fractionSpeed * length, minSpeed);
        this->camera.target = Vector2Add(this->camera.target, Vector2Scale(diff, speed*DELTA/length));
    }
}

void Game::update() {
    this->updateCamera();
    this->player.update();
    this->collisions();
}

void Game::render() {
    BeginDrawing();

        ClearBackground(RAYWHITE);
        this->draw();
    
    EndDrawing();
}

void Game::draw() {
    BeginMode2D(this->camera);
        this->map.draw();
        this->player.draw();
    EndMode2D();
}

void Game::collisions() {

    // X AXIS COLLISIONS
    for (Tile obstacle : *(this->map.getObstacle())) {
        Rectangle tile   = {obstacle.pos.x, obstacle.pos.y, TILE_SIZE, TILE_SIZE};
        Rectangle player = {this->player.getPosition().x, this->player.getPosition().y - this->player.getVelocity().y, TILE_SIZE, TILE_SIZE};
        
        if (CheckCollisionRecs(player, tile)) {
            this->player.isColliding("xAxis", tile.x);
            break;
        }
        
    }

    // Y AXIS COLLISIONS
    for (Tile obstacle : *(this->map.getObstacle())) {
        Rectangle tile   = {obstacle.pos.x, obstacle.pos.y, TILE_SIZE, TILE_SIZE};
        Rectangle player = {this->player.getPosition().x, this->player.getPosition().y, TILE_SIZE, TILE_SIZE};
        
        if (CheckCollisionRecs(player, tile)) {
            this->player.isColliding("yAxis", tile.y);
            break;
        }
        
    }

}

void Game::loadTextures() {
    this->map.loadTextures();
    this->player.loadTextures();
}
