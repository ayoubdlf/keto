#include "../include/menu.hpp"
#include "../include/game.hpp"

Menu::Menu() {
    this->state = Start;
}

Menu::~Menu() {}

void Menu::drawStart() {
    // TODO: Where the textures are going to be positionated?
    // TODO: Having enum as index for textures is more suitable

    /* Title */
    // Texture2D titleTexture = LoadTexture("assets/menu/title.png");
    // Vector2 title          = { GetScreenWidth() / 2.0f, GetScreenHeight() * 0.2f };
    // float titleScale       = 0.2f;
    // DrawTextureEx(titleTexture, { title.x - (titleTexture.width * titleScale)/2.0f, title.y - (titleTexture.height * titleScale)/2.0f }, 0.0f, titleScale, WHITE);

    /* play */
    // Texture2D playTexture = LoadTexture("assets/menu/play.png");
    // Vector2 play          = { GetScreenWidth() / 2.0f, GetScreenHeight() * 0.6f };
    // float playScale       = 0.3f;
    // DrawTextureEx(playTexture, { play.x - (playTexture.width * playScale)/2.0f, play.y - (playTexture.height * playScale)/2.0f }, 0.0f, playScale, WHITE);

    /* =============================================================================== */

    /* pause */
    Vector2 pause = { GetScreenWidth() / 2.0f, GetScreenHeight() * 0.3f };
    DrawTextEx(GetFontDefault(), "Game Over" , pause , 20.0f , 5.0f , BLACK);


    /* retry */
    Vector2 retry = { GetScreenWidth() * 0.45f, GetScreenHeight() * 0.6f };
    DrawTextEx(GetFontDefault(), "Retry" , retry , 20.0f , 5.0f , BLACK);

    /* play */
    Vector2 play = { GetScreenWidth() * 0.55f, GetScreenHeight() * 0.6f };
    DrawTextEx(GetFontDefault(), "Play" , play , 20.0f , 5.0f , BLACK);

}

void Menu::drawLevels() {}

void Menu::drawGameOver() {
    Texture2D gameOverTexture = LoadTexture("assets/menu/text/gameOver.png");
    Vector2 gameOver          = { GetScreenWidth() / 2.0f, GetScreenHeight() * 0.3f };
    float gameOverScale       = 0.15f;
    DrawTextureEx(gameOverTexture, { gameOver.x - (gameOverTexture.width * gameOverScale)/2.0f, gameOver.y - (gameOverTexture.height * gameOverScale)/2.0f }, 0.0f, gameOverScale, WHITE);

    /* retry */
    Texture2D retryTexture = LoadTexture("assets/menu/icons/retry.png");
    Vector2 retry          = { GetScreenWidth() * 0.45f, GetScreenHeight() * 0.6f };
    float retryScale       = 0.15f;
    DrawTextureEx(retryTexture, { retry.x - (retryTexture.width * retryScale)/2.0f, retry.y - (retryTexture.height * retryScale)/2.0f }, 0.0f, retryScale, WHITE);

    /* levels */
    Texture2D levelsTexture = LoadTexture("assets/menu/icons/levels.png");
    Vector2 levels          = { GetScreenWidth() * 0.55f, GetScreenHeight() * 0.6f };
    float levelsScale       = 0.15f;
    DrawTextureEx(levelsTexture, { levels.x - (levelsTexture.width * levelsScale)/2.0f, levels.y - (levelsTexture.height * levelsScale)/2.0f }, 0.0f, levelsScale, WHITE);

}

void Menu::drawPlaying() {
}

void Menu::updateStart() {
    Vector2 mouse         = GetMousePosition();
    
    Rectangle playButton  = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f, 200, 100 };
    playButton.x -= playButton.width / 2;
    playButton.y -= playButton.height / 2;

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse, playButton)) {
        this->state = Playing;
    }

}

void Menu::updateLevels() {}
void Menu::updateGameOver() {}
void Menu::updatePlaying() {}

void Menu::draw() {
    switch (this->state) {
        case Start        : this->drawStart() ; break;
        case LevelSelection : this->drawLevels()  ; break;
        case GameOver       : this->drawGameOver(); break;
        case Playing        : this->drawPlaying(); break;
        default: break;
    }
}

void Menu::update() {
    switch (this->state) {
        case Start        : this->updateStart() ; break;
        case LevelSelection : this->updateLevels()  ; break;
        case GameOver       : this->updateGameOver(); break;
        case Playing        : this->updatePlaying(); break;
        default: break;
    }
}

void Menu::loadTexture() {}

state Menu::getState() {
    return this->state;
}