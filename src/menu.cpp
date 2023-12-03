#include "../include/menu.hpp"
#include "../include/game.hpp"

Menu::Menu() {
    this->state       = Start;
    this->counter     = 0;
    this->currentSkin = 0;    
}

Menu::~Menu() {}


bool Menu::isButtonHovered(texture texture) {
    Vector2 mouse    = GetScreenToWorld2D(GetMousePosition(), Game::getInstance()->getFixedCamera());

    Rectangle button = { 
        .x      = texture.position.x,
        .y      = texture.position.y,
        .width  = texture.texture.width  * texture.scale,
        .height = texture.texture.height * texture.scale
    };

    return CheckCollisionPointRec(mouse, button);
}

bool Menu::isButtonClicked(texture texture) {
    Vector2 mouse    = GetScreenToWorld2D(GetMousePosition(), Game::getInstance()->getFixedCamera());

    Rectangle button = { 
        .x      = texture.position.x,
        .y      = texture.position.y,
        .width  = texture.texture.width  * texture.scale,
        .height = texture.texture.height * texture.scale
    };

    return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse, button);
}

// DRAW

void Menu::drawStart() {
    Vector2 window = GetScreenToWorld2D({ (float)GetScreenWidth(), (float)GetScreenHeight() }, Game::getInstance()->getFixedCamera());
    
    /* Title */
    this->textures[menu::Keto].position = {
        .x = (window.x / 2.0f) - (this->textures[menu::Keto].texture.width * this->textures[menu::Keto].scale) / 2.0f,
        .y = window.y * 0.1f
    };

    DrawTextureEx(this->textures[menu::Keto].texture, this->textures[menu::Keto].position, 0.0f, this->textures[menu::Keto].scale, WHITE);

    /* Play Button */
    this->textures[menu::Play].position = {
        .x = (window.x / 2.0f) - (this->textures[menu::Play].texture.width * this->textures[menu::Play].scale) / 2.0f,
        .y = window.y * 0.4f
    };

    DrawTextureEx(this->textures[menu::Play].texture, this->textures[menu::Play].position, 0.0f, this->textures[menu::Play].scale, WHITE);

    /* Load Button */
    this->textures[menu::Load].position = {
        .x = (window.x / 2.0f) - (this->textures[menu::Load].texture.width * this->textures[menu::Load].scale) / 2.0f,
        .y = window.y * 0.5f
    };

    DrawTextureEx(this->textures[menu::Load].texture, this->textures[menu::Load].position, 0.0f, this->textures[menu::Load].scale, WHITE);

    /* Skins Button */
    this->textures[menu::Skins].position = {
        .x = (window.x / 2.0f) - (this->textures[menu::Skins].texture.width * this->textures[menu::Skins].scale) / 2.0f,
        .y = window.y * 0.6f
    };

    DrawTextureEx(this->textures[menu::Skins].texture, this->textures[menu::Skins].position, 0.0f, this->textures[menu::Skins].scale, WHITE);


    /* Exit Button */
    this->textures[menu::Exit].position = {
        .x = (window.x / 2.0f) - (this->textures[menu::Exit].texture.width * this->textures[menu::Exit].scale) / 2.0f,
        .y = window.y * 0.7f
    };

    DrawTextureEx(this->textures[menu::Exit].texture, this->textures[menu::Exit].position, 0.0f, this->textures[menu::Exit].scale, WHITE);
}

void Menu::drawPlaying() {
    Vector2 window = GetScreenToWorld2D({ (float)GetScreenWidth(), (float)GetScreenHeight() }, Game::getInstance()->getFixedCamera());

    /* Pause Button */
    this->textures[menu::Pause].position = {
        .x = window.x - (this->textures[menu::Pause].texture.width * this->textures[menu::Pause].scale) * 1.5f,
        .y = window.y * 0.02f
    };

    DrawTextureEx(this->textures[menu::Pause].texture, this->textures[menu::Pause].position, 0.0f, this->textures[menu::Pause].scale, WHITE);
}

void Menu::drawPause() {
    Vector2 window = GetScreenToWorld2D({ (float)GetScreenWidth(), (float)GetScreenHeight() }, Game::getInstance()->getFixedCamera());
    
    /* Title */
    this->textures[menu::Keto].position = {
        .x = (window.x / 2.0f) - (this->textures[menu::Keto].texture.width * this->textures[menu::Keto].scale) / 2.0f,
        .y = window.y * 0.1f
    };

    DrawTextureEx(this->textures[menu::Keto].texture, this->textures[menu::Keto].position, 0.0f, this->textures[menu::Keto].scale, WHITE);

    /* Resume Button */
    this->textures[menu::Play].position = {
        .x = (window.x / 2.0f) - (this->textures[menu::Play].texture.width * this->textures[menu::Play].scale) / 2.0f,
        .y = window.y * 0.4f
    };

    DrawTextureEx(this->textures[menu::Play].texture, this->textures[menu::Play].position, 0.0f, this->textures[menu::Play].scale, WHITE);

    /* Save Button */
    this->textures[menu::Save].position = {
        .x = (window.x / 2.0f) - (this->textures[menu::Save].texture.width * this->textures[menu::Save].scale) / 2.0f,
        .y = window.y * 0.5f
    };

    DrawTextureEx(this->textures[menu::Save].texture, this->textures[menu::Save].position, 0.0f, this->textures[menu::Save].scale, WHITE);

    /* Exit Button */
    this->textures[menu::Exit].position = {
        .x = (window.x / 2.0f) - (this->textures[menu::Exit].texture.width * this->textures[menu::Exit].scale) / 2.0f,
        .y = window.y * 0.6f
    };

    DrawTextureEx(this->textures[menu::Exit].texture, this->textures[menu::Exit].position, 0.0f, this->textures[menu::Exit].scale, WHITE);

}

void Menu::drawSkins() {
    Vector2 window   = GetScreenToWorld2D({ (float)GetScreenWidth(), (float)GetScreenHeight() }, Game::getInstance()->getFixedCamera());

    /* Left Button */
    this->textures[menu::Left].position = {
        .x = (window.x * 0.3f) - (this->textures[menu::Left].texture.height * this->textures[menu::Left].scale),
        .y = (window.y / 2.0f) - (this->textures[menu::Right].texture.height * this->textures[menu::Right].scale) / 2.0f
    };

    DrawTextureEx(this->textures[menu::Left].texture, this->textures[menu::Left].position, 0.0f, this->textures[menu::Left].scale, WHITE);

    /* Right Button */
    this->textures[menu::Right].position = {
        .x = window.x * 0.7f,
        .y = (window.y / 2.0f) - (this->textures[menu::Right].texture.height * this->textures[menu::Right].scale) / 2.0f
    };

    DrawTextureEx(this->textures[menu::Right].texture, this->textures[menu::Right].position, 0.0f, this->textures[menu::Right].scale, WHITE);
    
    /* Current Skin */
    this->skins[this->currentSkin].position = {
        .x = (window.x / 2.0f) - (this->skins[this->currentSkin].texture.width * this->skins[this->currentSkin].scale) / 2.0f,
        .y = (window.y / 2.0f) - (this->skins[this->currentSkin].texture.height * this->skins[this->currentSkin].scale) / 2.0f
    };

    DrawTextureEx(this->skins[this->currentSkin].texture, this->skins[this->currentSkin].position, 0.0f, this->skins[this->currentSkin].scale, WHITE);
    
    /* Play Button */
    this->textures[menu::Play].position = {
        .x = (window.x / 2.0f) - (this->textures[menu::Play].texture.width * this->textures[menu::Play].scale) / 2.0f,
        .y = window.y * 0.8f
    };

    DrawTextureEx(this->textures[menu::Play].texture, this->textures[menu::Play].position, 0.0f, this->textures[menu::Play].scale, WHITE);

}

void Menu::drawCompleted() {
    Vector2 window = GetScreenToWorld2D({ (float)GetScreenWidth(), (float)GetScreenHeight() }, Game::getInstance()->getFixedCamera());

    /* Congratulations message */
    this->textures[menu::End].position = {
        .x = (window.x / 2.0f) - (this->textures[menu::End].texture.width * this->textures[menu::End].scale)  / 2.0f,
        .y = (window.y / 2.0f) - (this->textures[menu::End].texture.height * this->textures[menu::End].scale) / 2.0f,
    };

    DrawTextureEx(this->textures[menu::End].texture, this->textures[menu::End].position, 0.0f, this->textures[menu::End].scale, WHITE);
}

void Menu::drawGameOver() {
    Vector2 window = GetScreenToWorld2D({ (float)GetScreenWidth(), (float)GetScreenHeight() }, Game::getInstance()->getFixedCamera());

    /* Game Over */
    this->textures[menu::GameOver].position = {
        .x = (window.x / 2.0f) - (this->textures[menu::GameOver].texture.width * this->textures[menu::GameOver].scale)  / 2.0f,
        .y = (window.y / 2.0f) - (this->textures[menu::GameOver].texture.height * this->textures[menu::GameOver].scale) / 2.0f,
    };

    DrawTextureEx(this->textures[menu::GameOver].texture, this->textures[menu::GameOver].position, 0.0f, this->textures[menu::GameOver].scale, WHITE);
}

// UPDATE

void Menu::updateStart() {

    this->textures[menu::Play].scale  = this->isButtonHovered(this->textures[menu::Play])  ? 2.1f : 2.0f;
    this->textures[menu::Load].scale  = this->isButtonHovered(this->textures[menu::Load])  ? 2.1f : 2.0f;
    this->textures[menu::Skins].scale = this->isButtonHovered(this->textures[menu::Skins]) ? 2.1f : 2.0f;
    this->textures[menu::Exit].scale  = this->isButtonHovered(this->textures[menu::Exit])  ? 2.1f : 2.0f;

    if(this->isButtonClicked(this->textures[menu::Play])) {
        Game::getInstance()->reset();
        this->state = Playing;
        return;
    }

    if(this->isButtonClicked(this->textures[menu::Load])) {
        Game::getInstance()->load();
        this->state = Playing;
        return;
    }

    if(this->isButtonClicked(this->textures[menu::Skins])) {
        this->state = Skins;
        return;
    }

    if(this->isButtonClicked(this->textures[menu::Exit])) {
        this->state = Exit;
    }
}

void Menu::updatePlaying() {
    if(this->isButtonClicked(this->textures[menu::Pause])) {
        this->state = Pause;
    }
}

void Menu::updatePause() {

    this->textures[menu::Play].scale = this->isButtonHovered(this->textures[menu::Play]) ? 2.1f : 2.0f;
    this->textures[menu::Save].scale = this->isButtonHovered(this->textures[menu::Save]) ? 2.1f : 2.0f;
    this->textures[menu::Exit].scale = this->isButtonHovered(this->textures[menu::Exit]) ? 2.1f : 2.0f;

    if(this->isButtonClicked(this->textures[menu::Play])) {
        this->state = Playing;
        return;
    }
    
    if(this->isButtonClicked(this->textures[menu::Save])) {
        Game::getInstance()->save();
        return;
    }

    if(this->isButtonClicked(this->textures[menu::Exit])) {
        this->state = Exit;
        return;
    }

}

void Menu::updateSkins() {

    if(this->isButtonClicked(this->textures[menu::Left]) || IsKeyPressed(KEY_LEFT)) {
        this->currentSkin -= 1;
        if(this->currentSkin == -1) { this->currentSkin = (int)this->skins.size() - 1; }
    }

    if(this->isButtonClicked(this->textures[menu::Right]) || IsKeyPressed(KEY_RIGHT)) {
        this->currentSkin += 1;
        if(this->currentSkin == (int)this->skins.size()) { this->currentSkin = 0; }
    }

    if(this->isButtonClicked(this->textures[menu::Play])) {
        Game::getInstance()->reset();
        Game::getInstance()->getPlayer().setName(this->skinsName[this->currentSkin]);
        Game::getInstance()->getPlayer().loadTextures();
        this->state = Playing;
        return;
    }
}

void Menu::updateGameOver() {
    this->counter += 1;

    if(this->counter == 210) {
        this->state = Start;
        this->counter = 0;
    }
}

void Menu::updateCompleted() {
    this->counter += 1;

    if(this->counter == 240) {
        this->state = Start;
        this->counter = 0;
    }
}



void Menu::draw() {
    switch (this->state) {
        case Start     : this->drawStart(); break;
        case Playing   : this->drawPlaying(); break;
        case Pause     : this->drawPause(); break;
        case Skins     : this->drawSkins(); break;
        case Completed : this->drawCompleted(); break;
        case GameOver  : this->drawGameOver(); break;
        default        : break;
    }
}

void Menu::update() {
    switch (this->state) {
        case Start     : this->updateStart() ; break;
        case Playing   : this->updatePlaying(); break;
        case Pause     : this->updatePause(); break;
        case Skins     : this->updateSkins(); break;
        case Completed : this->updateCompleted() ; break;
        case GameOver  : this->updateGameOver(); break;
        default        : break;
    }
}

void Menu::loadTextures() {
    std::string keto     = "assets/menu/keto.png";
    std::string play     = "assets/menu/play.png";
    std::string pause    = "assets/menu/pause.png";
    std::string load     = "assets/menu/load.png";
    std::string save     = "assets/menu/save.png";
    std::string skins    = "assets/menu/skins.png";
    std::string left     = "assets/menu/left.png";
    std::string right    = "assets/menu/right.png";
    std::string gameOver = "assets/menu/gameOver.png";
    std::string end      = "assets/menu/end.png";
    std::string exit     = "assets/menu/exit.png";

    this->textures[menu::Keto] = {
        .texture  = LoadTexture(keto.c_str()),
        .scale    = 6.0f,
        .position = {0.0f, 0.0f}
    };

    this->textures[menu::Play] = {
        .texture  = LoadTexture(play.c_str()),
        .scale    = 2.0f,
        .position = {0.0f, 0.0f}
    };

    this->textures[menu::Pause] = {
        .texture  = LoadTexture(pause.c_str()),
        .scale    = 2.0f,
        .position = {0.0f, 0.0f}
    };

    this->textures[menu::Load] = {
        .texture  = LoadTexture(load.c_str()),
        .scale    = 2.0f,
        .position = {0.0f, 0.0f}
    };

    this->textures[menu::Save] = {
        .texture  = LoadTexture(save.c_str()),
        .scale    = 2.0f,
        .position = {0.0f, 0.0f}
    };

    this->textures[menu::Skins] = {
        .texture  = LoadTexture(skins.c_str()),
        .scale    = 2.0f,
        .position = {0.0f, 0.0f}
    };

    this->textures[menu::Left] = {
        .texture  = LoadTexture(left.c_str()),
        .scale    = 3.0f,
        .position = {0.0f, 0.0f}
    };

    this->textures[menu::Right] = {
        .texture  = LoadTexture(right.c_str()),
        .scale    = 3.0f,
        .position = {0.0f, 0.0f}
    };

    this->textures[menu::GameOver] = {
        .texture  = LoadTexture(gameOver.c_str()),
        .scale    = 5.0f,
        .position = {0.0f, 0.0f}
    };

    this->textures[menu::End] = {
        .texture  = LoadTexture(end.c_str()),
        .scale    = 2.0f,
        .position = {0.0f, 0.0f}
    };

    this->textures[menu::Exit] = {
        .texture  = LoadTexture(exit.c_str()),
        .scale    = 2.0f,
        .position = {0.0f, 0.0f}
    };


    this->loadSkins();
}

void Menu::loadSkins() {
    for (fs::directory_entry entry : fs::directory_iterator("assets/players")) {
        if(entry.path().filename().string()[0] != '.' && entry.path().filename().string() != "enemy") {
            // skinPath = "assets/players/NAME/NAME.png"
            std::string skinPath = entry.path().string() + "/" + entry.path().filename().string() + ".png";

            texture skin = {
                .texture  = LoadTexture(skinPath.c_str()),
                .scale    = 5.0f,
                .position = {0.0f, 0.0f}
            };

            this->skins.push_back(skin);
            this->skinsName.push_back(entry.path().filename().string());
        }
    }    
}

utils::state Menu::getState() {
    return this->state;
}

void Menu::setState(utils::state state) {
    this->state = state;
}
