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
            DrawTexture(this->tilesMap[i][j].texture, this->tilesMap[i][j].pos.x, this->tilesMap[i][j].pos.y, RAYWHITE);
        }
    }
}

void Map::loadTiles() {
    this->tilesMap.resize(this->map.size(), std::vector<Tile>(this->map[0].size()));

    for (int i = 0; i < this->map.size(); i++) {
        for (int j = 0; j < this->map[i].size(); j++) {
            int index = findIndexById(this->map[i][j], this->textures);
            Vector2 pos = { j * TILE_SIZE, i * TILE_SIZE };
            this->tilesMap[i][j] = { this->textures[index].texture, pos };
        }
    }

}

void Map::loadTextures() {

    int max = getMax(this->map);
    std::vector<int> tilesIds; // here we're going to store unique `tiles id` found in the map file

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (!isInsideVect(map[i][j], tilesIds)) {
                tilesIds.push_back(map[i][j]);
            }
        }
    }

    this->textures.resize(tilesIds.size());

    for (int i = 0; i < tilesIds.size(); i++) {
        std::string tilePath = "assets/map/tiles/" + addZeros(tilesIds[i], max) + ".png";
        this->textures[i] = { tilesIds[i], LoadTexture(tilePath.c_str())};
    }

    this->loadTiles();
}

void Map::load(std::string filepath) {
    std::ifstream file (filepath);
    std::string line;

    if (!file.is_open()) assert(false && "[!] Unable to open map file");

    getMapSize(&file, &this->width, &this->height);
    mapToVector(&file, &this->map);

    file.close();
}

void Map::unloadTextures() {
    for (utils::Texture texture : this->textures) {
        UnloadTexture(texture.texture);
    }
}
