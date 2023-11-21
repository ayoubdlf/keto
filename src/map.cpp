#include "../include/map.hpp"

// MAP Methods

Map::~Map() {}

void Map::draw() {
    for(int i = 0; i < (int)this->tilesMap.size(); i++) {
        for(int j = 0; j < (int)this->tilesMap[i].size(); j++) {
            DrawTexture(this->tilesMap[i][j].texture, this->tilesMap[i][j].pos.x, this->tilesMap[i][j].pos.y, RAYWHITE);
        }
    }
}

std::vector<Tile>& Map::getObstacles() {
    return this->obstacles;
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
                    .pos = pos,
                    .type = type
                };

                if(this->tilesMap[i][j].type != Air) {
                    this->tilesMap[i][j].texture = this->textures[index].texture;
                }

                if(this->tilesMap[i][j].type == Obstacle) {
                    this->obstacles.push_back(this->tilesMap[i][j]);
                }

            }
            
        }
    }

}

void Map::loadTextures() {

    int max = getMax(this->map);
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
        std::string tilePath = "assets/map/tiles/" + addZeros(tilesNumber[i], max) + ".png";
        this->textures[i] = { tilesNumber[i], LoadTexture(tilePath.c_str())};
    }
    this->loadTiles();
}

void Map::load(std::string filepath) {
    std::ifstream file (filepath);
    std::string line;

    if (!file.is_open()) assert(false && "[!] Unable to open map file");

    mapToVector(&file, &this->map);

    file.close();
}
