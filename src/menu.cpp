#include "../include/menu.hpp"
#include "../include/game.hpp"

Menu::Menu() {
    this->state  = Start;

    this->textures[menu::Play].scale = 2.0f;
    this->textures[menu::Load].scale = 2.0f;
    this->textures[menu::Exit].scale = 2.0f;
    
    this->textures[menu::Play].position = {0.0f, 0.0f};
    this->textures[menu::Load].position = {0.0f, 0.0f};
    this->textures[menu::Exit].position = {0.0f, 0.0f};
}

Menu::~Menu() {}

void Menu::drawStart() {
    Vector2 window = GetScreenToWorld2D({ (float)GetScreenWidth(), (float)GetScreenHeight() }, Game::getInstance()->getFixedCamera());
    
    /* Title */
    // TODO: title pixel
    int fontSize     = 60.0f;
    int middle       = MeasureText("Keto", fontSize) / 2;
    Vector2 titlePos = { (window.x / 2.0f) - middle, window.y * 0.1f };
    DrawTextEx(Game::getInstance()->getFont(), "Keto", titlePos, fontSize, 1.0f, BLACK);

    /* Play Button */
    this->textures[menu::Play].position = {
        .x = (window.x / 2.0f) - (this->textures[menu::Play].texture.width * this->textures[menu::Play].scale) / 2.0f,
        .y = window.y * 0.3f
    };

    DrawTextureEx(this->textures[menu::Play].texture, this->textures[menu::Play].position, 0.0f, this->textures[menu::Play].scale, WHITE);

    /* Load Button */
    this->textures[menu::Load].position = {
        .x = (window.x / 2.0f) - (this->textures[menu::Load].texture.width * this->textures[menu::Load].scale) / 2.0f,
        .y = window.y * 0.4f
    };

    DrawTextureEx(this->textures[menu::Load].texture, this->textures[menu::Load].position, 0.0f, this->textures[menu::Load].scale, WHITE);

    /* Exit Button */
    this->textures[menu::Exit].position = {
        .x = (window.x / 2.0f) - (this->textures[menu::Exit].texture.width * this->textures[menu::Exit].scale) / 2.0f,
        .y = window.y * 0.5f
    };

    DrawTextureEx(this->textures[menu::Exit].texture, this->textures[menu::Exit].position, 0.0f, this->textures[menu::Exit].scale, WHITE);
}

void Menu::drawLevels() {}

void Menu::drawGameOver() {
    // DrawTextEx(Game::getInstance()->getFont(), "Game Over" , { window.x/2.0f, window.y/2.0f }, 20.0f , 5.0f , BLACK);
}

void Menu::drawPlaying() {
}

void Menu::updateStart() {
    Vector2 mouse   = GetScreenToWorld2D(GetMousePosition(), Game::getInstance()->getFixedCamera());

    /* Play Button */
    
    Rectangle play  = { 
        .x      = this->textures[menu::Play].position.x,
        .y      = this->textures[menu::Play].position.y,
        .width  = this->textures[menu::Play].texture.width  * this->textures[menu::Play].scale,
        .height = this->textures[menu::Play].texture.height * this->textures[menu::Play].scale
    };

    this->textures[menu::Play].scale = CheckCollisionPointRec(mouse, play) ? 2.1f : 2.0f;

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse, play)) {
        Game::getInstance()->reset();
        this->state = Playing;
        return;
    }

    /* Load Button */    
    Rectangle load  = { 
        .x      = this->textures[menu::Load].position.x,
        .y      = this->textures[menu::Load].position.y,
        .width  = this->textures[menu::Load].texture.width  * this->textures[menu::Load].scale,
        .height = this->textures[menu::Load].texture.height * this->textures[menu::Load].scale
    };

    this->textures[menu::Load].scale = CheckCollisionPointRec(mouse, load) ? 2.1f : 2.0f;

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse, load)) {
        Game::getInstance()->load();
        this->state = Playing;
        return;
    }

    /* EXIT BUTTON */    
    Rectangle exit  = { 
        .x      = this->textures[menu::Exit].position.x,
        .y      = this->textures[menu::Exit].position.y,
        .width  = this->textures[menu::Exit].texture.width  * this->textures[menu::Exit].scale,
        .height = this->textures[menu::Exit].texture.height * this->textures[menu::Exit].scale
    };

    this->textures[menu::Exit].scale = CheckCollisionPointRec(mouse, exit) ? 2.1f : 2.0f;

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse, exit)) {
        this->state = Exit;
        return;
    }

}

void Menu::updateLevels() {}
void Menu::updateGameOver() {}
void Menu::updatePlaying() {}

void Menu::draw() {
    switch (this->state) {
        case Start          : this->drawStart() ; break;
        case LevelSelection : this->drawLevels()  ; break;
        case GameOver       : this->drawGameOver(); break;
        case Playing        : this->drawPlaying(); break;
        default: break;
    }
}

void Menu::update() {
    switch (this->state) {
        case Start          : this->updateStart() ; break;
        case LevelSelection : this->updateLevels()  ; break;
        case GameOver       : this->updateGameOver(); break;
        case Playing        : this->updatePlaying(); break;
        default: break;
    }
}

void Menu::loadTextures() {
    std::string play     = "assets/menu/play.png";
    std::string load     = "assets/menu/load.png";
    std::string exit     = "assets/menu/exit.png";
    // std::string retry    = "assets/menu/retry.png";

    this->textures[menu::Play].texture = LoadTexture(play.c_str());
    this->textures[menu::Load].texture = LoadTexture(load.c_str());
    this->textures[menu::Exit].texture = LoadTexture(exit.c_str());
    // this->textures[menu::Retry].texture = LoadTexture(retry.c_str());
    // TODO: this->textures[menu::Levels].texture
}

state Menu::getState() {
    return this->state;
}