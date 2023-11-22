#include "../include/menu.hpp"
#include "../include/game.hpp"

Menu::Menu() {
    this->state = menuState::Welcome;
}

Menu::~Menu(){}

void Menu::drawWelcome() {
    int posX = HEIGHT;
    int posY = WIDTH;

    for(Texture2D buttons : this->texturesWelcome){

        DrawTexture(buttons,posX,posY,WHITE);
    }
}
void Menu::drawLevels() {}
void Menu::drawGameOver() {}

void Menu::draw() {
    switch (this->state) {
        case menuState::Welcome        : this->drawWelcome(); break;
        case menuState::LevelSelection : this->drawLevels(); break;
        case menuState::GameOver       : this->drawGameOver(); break;
        default: break;
    }
}

void Menu::update() {}
void Menu::updateWelcome() {}
void Menu::updateLevels() {}
void Menu::updateGameOver() {}

void Menu::loadTexture() {}