#include "../include/map.hpp"
#include "../include/utils.hpp"
#include <fstream>
#include <cassert>

Map::Map() {}

Map::~Map() {
    this->unloadTextures();
}

void Map::draw() {
    for (int i = 0; i < this->tilesMap.size(); i++) {
        for (int j = 0; j < this->tilesMap[i].size(); j++) {
            DrawTexture(this->tilesMap[i][j].texture, (int)this->tilesMap[i][j].pos.x, (int)this->tilesMap[i][j].pos.y, RAYWHITE);
        }
    }
}

void Map::loadTiles() {
    this->tilesMap.resize(this->height + 1, std::vector<utils::Tile>(this->width + 1));

    for (int i = 0; i < this->map.size(); i++) {
        for (int j = 0; j < this->map[i].size(); j++) {
            int index = utils::findIndexById(this->map[i][j], this->textures);
            if(index != -1) {
                Vector2 pos = {(float)j * TILE_SIZE, (float)i * TILE_SIZE};
                this->tilesMap[i][j] = {this->textures[index].texture, pos};
            }
        }
    }

}

void Map::loadTextures() {

    int max = utils::getMax(this->map);
    std::vector<int> tilesIds; // here we're going to store unique `tiles id` found in the map file

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (!utils::isInsideVect(map[i][j], tilesIds)) {
                tilesIds.push_back(map[i][j]);
            }
        }
    }

    this->textures.resize(tilesIds.size());

    for (int i = 0; i < tilesIds.size(); i++) {
        std::string tilePath = "assets/map/tiles/" + utils::addZeros(tilesIds[i], max) + ".png";
        this->textures[i] = { tilesIds[i], LoadTexture(tilePath.c_str())};
    }

    this->loadTiles();
}

void Map::load(std::string filepath) {
    std::ifstream file (filepath);
    std::string line;

    if (!file.is_open()) assert(false && "[!] Unable to open map file");

    utils::getMapSize(&file, &this->width, &this->height);
    this->map.resize(this->height + 1, std::vector<int>(this->width + 1));
    utils::mapToVector(&file, &this->map);
    file.close();
}

void Map::unloadTextures() {
    for (utils::Texture texture : this->textures) {
        UnloadTexture(texture.texture);
    }
}
