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
    InitAudioDevice();
    SetTargetFPS(60);
    SetTextureFilter(this->font.texture, TEXTURE_FILTER_POINT);
    // this->font  = LoadFontEx("assets/fonts/SF-Pro/SF-Pro-Text-Semibold.otf", 100, NULL, 0);
    this->font  = LoadFontEx("assets/fonts/SF-Compact/SF-Compact-Text-Semibold.otf", 100, NULL, 0);
    this->music = LoadMusicStream("assets/sounds/bg.mp3");
    /* Setting alerts to false */
    this->alertMessage.active = false;
    
    /* Init main camera */
    this->camera.target   = { width/2.0f, height/2.0f };
    this->camera.offset   = { width/2.0f, height/2.0f };
    this->camera.zoom     = ZOOM;
    this->camera.rotation = 0.0f;

    /* Init foreground camera (player stats, menu) */
    this->fixedCamera.target   = { 0 };
    this->fixedCamera.offset   = { 0 };
    this->fixedCamera.zoom     = ZOOM;
    this->fixedCamera.rotation = 0.0f;

    /* Menu textures */
    this->menu.loadTextures();

    /* Cursor textures */
    std::string targetPath = "assets/items/target.png";
    this->target = LoadTexture(targetPath.c_str());

    PlayMusicStream(this->music);
    HideCursor();
}

Game::~Game() {}

void Game::init() {
    /*  This method does nothing. But it's helpful in the main.cpp
        Calling this function before the game loop,
        will allow us to initialize out instance of the game singleton.
    */
}

void Game::reset(bool resetLevels) {

    if(resetLevels) {
        /* Create Levels */
        this->levels.create();
    }

    /* Reset all sprites and map */
    this->map.reset();
    this->player.reset();
    this->enemies.clear();
    this->enemies.shrink_to_fit();

    /* load map */
    this->map.load(this->levels.getCurrentLevelPath());
    this->map.loadTextures(); // i'm loading map textures now, because we need access to the tilesMap inside the initEnemies method;

    /* Init player */
    this->player.setName();
    this->player.useGun();
    this->player.loadTextures();

    /* Init enemies */
    this->initEnemies();

    /* Load textures */
    this->loadTextures();
}


/*
*   Returns ALL possible enemies positions
*/
std::vector<Vector2> Game::getAllEnemyPositions() {
    std::vector<std::vector<Tile>>& map = this->map.getTilesMap();

    std::vector<Vector2> positions;

    for (int y = 0; y < (int)map.size(); y++) {
        for (int x = 0; x < (int)map[y].size(); x++) {

            if(map[y][x].type == Air) {

                bool left         = isInsideMap(map, x-1, y)   ?  (map[y][x-1].type   == Air)       : false;
                bool right        = isInsideMap(map, x+1, y)   ?  (map[y][x+1].type   == Air)       : false;
                bool bottom_left  = isInsideMap(map, x-1, y+1) ?  (map[y+1][x-1].type == Obstacle ) : false;
                bool bottom_right = isInsideMap(map, x+1, y+1) ?  (map[y+1][x+1].type == Obstacle ) : false;
                bool bottom       = isInsideMap(map, x, y+1)   ?  (map[y+1][x].type   == Obstacle ) : false;

                if(left && right && bottom && bottom_left && bottom_right) {
                    positions.push_back(map[y][x].pos);
                }

            }

        }
    }

    return positions;
}

/*
*   Returns NB_ENEMIES possible enemy positions (and every position is far away from the other ones)
*/
std::vector<Vector2> Game::getPossibleEnemyPositions(int customDistance) {
    std::random_device rd;
    std::mt19937 mt(rd());

    std::vector<Vector2> positions = this->getAllEnemyPositions();

    int nb_enemies      = NB_ENEMIES;
    bool valid_distance = true; // false if the new enemy position is near another one (based on customDistance)
    std::vector<Vector2> available_positions;

    while (nb_enemies != 0 && positions.size() != 0) {
        std::shuffle(positions.begin(), positions.end(), mt);
        Vector2 newPos = positions.back();
        positions.pop_back();


        // Checking if the new possible position is far away from the other ones
        // We don't want enemies to be one next another one
        for (int i = 0; i < (int)available_positions.size(); i++) {
            int distance = (int)Vector2Distance(available_positions[i], newPos);

            if(distance < customDistance) {
                valid_distance = false;
                continue;
            }

        }

        if(valid_distance) {
            // Push back a new enemy position only if its distance is far away from the other enemies
            available_positions.push_back(newPos);
        }

        nb_enemies -= 1;
    }

    return available_positions;

}

void Game::initEnemies() {
    std::vector<Vector2> enemy_positions = this->getPossibleEnemyPositions(32*6);
    
    for (int i = 0; i < (int)enemy_positions.size(); i++) {
        this->enemies.emplace_back();
        this->enemies[i].setName("enemy");
        this->enemies[i].setPosition(enemy_positions[i]);
    }

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

Camera2D Game::getFixedCamera() {
    return this->fixedCamera;
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

Menu& Game::getMenu() {
    return this->menu;
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
    this->menu.update();

    if(this->menu.getState() == Playing) {
        UpdateMusicStream(this->music);
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
        } else {
            Game::getInstance()->getMenu().setState(GameOver);
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
    DrawTextEx(this->font, level.c_str(), { screenSize.x/2.0f - MeasureText(level.c_str(), fontSize), 20.0f }, fontSize, 1.0f, BLACK);
}

void Game::draw() {

    BeginMode2D(this->camera);
        if(this->menu.getState() == Playing) {

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
                int textMiddle = MeasureText(this->alertMessage.message.c_str(), 10.0f) / 2;
                DrawTextEx(this->font, this->alertMessage.message.c_str(), this->alertMessage.position, 10.0f, 1.0f, BLACK);
                this->alertMessage.position = { this->player.getRect().x + this->player.getRect().width/2 - textMiddle, this->alertMessage.position.y - 0.5f };
                this->alertMessage.time    -= 1;
                this->alertMessage.active   = (this->alertMessage.time != 0);
            }

        }

        // Draw our custom cursor
        this->drawTarget();

    EndMode2D();

    BeginMode2D(this->fixedCamera);
        if(this->menu.getState() == Playing) {
            this->player.drawStats();
            this->drawLevelNumber();
        }

        this->menu.draw();

    EndMode2D();
}

void Game::load() {

    this->levels.load();

    std::ifstream file("data.json");
    
    if (file.is_open()) {
        json data;
        file >> data;

        this->reset(false);
        this->player.loadData(data);
    } else {
        Game::getInstance()->reset();
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

    std::string playerName = this->player.getName();

    this->reset(false);

    this->map.load(this->levels.getCurrentLevelPath());
    this->player.setName(playerName);
    this->player.useGun();

    this->loadTextures();
}

void Game::loadTextures() {
    // this->map.loadTextures();
    this->player.loadTextures();

    for (int i = 0; i < (int)this->enemies.size(); i++) {
        if(this->enemies[i].isAlive()) {
            this->enemies[i].loadTextures();
        }
    }
}

Font& Game::getFont() {
    return this->font;
}