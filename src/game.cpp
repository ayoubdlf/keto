#include <iostream>
#include <raylib.h>
#include "../include/game.hpp"

Game::Game(int width, int height) {

    // Init window
    SetTraceLogLevel(LOG_WARNING); // remove annoying logging
    SetConfigFlags(FLAG_WINDOW_HIGHDPI); // DPI
    InitWindow(width, height, "Keto");
    SetTargetFPS(60);

    // Load map
    this->map.load("assets/map/map.txt");

    this->camera.offset = (Vector2){ width/2.0f, height/2.0f };
    this->camera.zoom = 0.8f;
    this->camera.rotation = 0.0f;
}

Game::~Game() {
    this->clean();
}

void Game::input() {
    this->player.handleInputs();
}

void Game::update() {
    this->camera.target = this->player.getPosition();
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
    this->player.loadTexture();
}

void Game::unloadTextures() {
    this->map.unloadTextures();
    this->player.unloadTexture();
}

void Game::clean() {
    this->unloadTextures();
}
