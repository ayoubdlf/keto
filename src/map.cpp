#include "../include/map.hpp"

// MAP Methods

Map::Map() {
    this->framesCounter = 0;
    this->framesSpeed   = X_FRAME_SPEED * 0.8; 
}

Map::~Map() {}

void Map::drawPowerUps() {
    for (int i = 0; i < (int)this->powerUps.size(); i++) {
        Rectangle source = this->powerUps[i].frames;
        DrawTextureRec(this->powerUps[i].texture, source, this->powerUps[i].pos, WHITE);
    }
}

void Map::draw() {
    for(int i = 0; i < (int)this->tilesMap.size(); i++) {
        for(int j = 0; j < (int)this->tilesMap[i].size(); j++) {
            if(!isPowerUp(this->tilesMap[i][j].type)) {
                DrawTexture(this->tilesMap[i][j].texture, this->tilesMap[i][j].pos.x, this->tilesMap[i][j].pos.y, WHITE);
            }
        }
    }

    this->drawPowerUps();
}

void Map::usePowerUp(int i) {
    this->powerUps.erase(this->powerUps.begin() + i);
}

void Map::update() {
    this->framesCounter += 1;

    if (this->framesCounter >= (60 / this->framesSpeed)) {
        this->framesCounter = 0;

        for(int i = 0; i < (int)this->powerUps.size(); i++) {
            this->powerUps[i].currentFrame  = (this->powerUps[i].currentFrame + 1) % int(this->powerUps[i].texture.width / this->tileWidth + 1);
        }
    }
    
    // Update texture X axis
    for(int i = 0; i < (int)this->powerUps.size(); i++) {
        this->powerUps[i].frames.x = this->powerUps[i].currentFrame * this->tileWidth;
    }

}

std::vector<std::vector<int>>& Map::getMap() {
    return this->map;
}

std::vector<std::vector<Tile>>& Map::getTilesMap() {
    return this->tilesMap;
}

std::vector<Tile>& Map::getObstacles() {
    return this->obstacles;
}

std::vector<Tile>& Map::getPowerUps() {
    return this->powerUps;
}

Tile Map::getCheckPoint() {
    return this->checkPoint;
}

void Map::loadTiles() {
    this->tilesMap.resize(this->map.size(), std::vector<Tile>(this->map[0].size()));

    for(int i = 0; i < (int)this->map.size(); i++) {
        for(int j = 0; j < (int)this->map[i].size(); j++) {

            int index = findIndexById(this->map[i][j], this->textures);

            if(index != -1) {

                Vector2 pos = { float(j * this->textures[index].texture.width), float(i * this->textures[index].texture.height) };
                utils::TileType type = utils::getTileTypeByCode(this->map[i][j]);
                
                this->tilesMap[i][j] = {
                    .texture = this->textures[index].texture,
                    .pos = pos,
                    .type = type
                };

                if(isPowerUp(this->tilesMap[i][j].type)) {
                    this->tilesMap[i][j].pos          = { float(j * this->textures[index].frames.width), float(i * this->textures[index].frames.height) };
                    this->tilesMap[i][j].frames       =  this->textures[index].frames;
                    this->tilesMap[i][j].currentFrame = 0;

                    this->powerUps.push_back(this->tilesMap[i][j]);
                }

                if(this->tilesMap[i][j].type == CheckPoint) {
                    this->checkPoint = this->tilesMap[i][j];
                }

                if(this->tilesMap[i][j].type == Obstacle) {
                    this->obstacles.push_back(this->tilesMap[i][j]);
                }

            } else {
                // If the tile is Air
                if(utils::getTileTypeByCode(this->map[i][j]) == Air) {

                    this->tilesMap[i][j] = {
                        .pos = {
                            .x = float(j * this->textures.back().texture.width),
                            .y = float(i * this->textures.back().texture.height)
                        },
                        .type = Air
                    };

                }
            }
            
        }
    }

    this->mapWidth  = this->tilesMap[0].size() * this->obstacles[0].texture.width;
    this->mapHeight = this->tilesMap.size()    * this->obstacles[0].texture.height;
}

void Map::loadTextures() {
    
    std::vector<int> tilesNumber; // here we're going to store unique `tile numbers` found in the map file

    for(int i = 0; i < (int)map.size(); i++) {
        for(int j = 0; j < (int)map[i].size(); j++) {
            if (map[i][j] != 0 && !isInsideVect(map[i][j], tilesNumber)) {
                tilesNumber.push_back(map[i][j]);
            }
        }
    }

    this->textures.resize(tilesNumber.size());

    for(int i = 0; i < (int)tilesNumber.size(); i++) {
        std::string tilePath = this->mapPath + "tiles/" +std::to_string(tilesNumber[i]) + ".png";
       
        if(tilesNumber[i] >= 1 && tilesNumber[i] <= 5) {
            std::string customTilePath;

            switch (tilesNumber[i]) {
                case 1: customTilePath = "assets/items/powerups/coin.png"    ; break;
                case 2: customTilePath = "assets/items/powerups/heart.png"   ; break;
                case 3: customTilePath = "assets/items/powerups/bullet.png"  ; break;
                case 4: customTilePath = "assets/items/powerups/medKit.png"  ; break;
                case 5: customTilePath = "assets/items/powerups/luckyBox.png"; break;
                default: break;
            }

            this->textures[i] = this->loadCustomTexture(tilesNumber[i], tilePath, customTilePath);

        } else {
            this->textures[i] = {
                .id      = tilesNumber[i],
                .texture = LoadTexture(tilePath.c_str())
            };
        }
        
    }

    this->loadTiles();
}

void Map::load(std::string filepath) {
    this->mapPath = filepath.substr(0, filepath.find_last_of('/')) + "/";
    std::ifstream file (filepath);
    std::string line;

    if (!file.is_open()) assert(false && "[!] Unable to open map file");

    mapToVector(&file, &this->map);

    file.close();
}

CustomTexture Map::loadCustomTexture(int id, std::string path, std::string custom) {
    Texture2D texture       = LoadTexture(path.c_str());
    Texture2D customTexture = LoadTexture(custom.c_str());
    
    this->tileWidth  = texture.width;
    this->tileHeight = texture.height;

    return {
        .id      = id,
        .texture = customTexture,
        .frames  = {
            0.0f,
            0.0f,
            (float)texture.width,
            (float)texture.height
        }
    };

}

int Map::getWidth() {
    return this->mapWidth;
}

int Map::getHeight() {
    return this->mapHeight;
}

void Map::reset() {
    this->~Map();
    new (this) Map();
}