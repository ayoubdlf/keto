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
}

Game::~Game() {
    this->clean();
}

void Game::input() {
    this->player.handleInputs();
}

void Game::update() {
    this->collisions();
    this->player.update();
}

void Game::render() {
    BeginDrawing();

        ClearBackground(RAYWHITE);
        this->draw();
    
    EndDrawing();
}

void Game::draw() {
    this->map.draw();
    this->player.draw();
}

void Game::collisions() {

    Vector2 playerDest = this->player.getDestination();

    if(isColliding(this->player.getRect(playerDest), this->map.getMap())) {
        this->player.colliding();
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