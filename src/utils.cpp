#include "../include/utils.hpp"

void utils::getMapSize(std::ifstream *file, int *width, int *height) {
    std::string line;
    getline(*file, line);
    *width = stoi(line.substr(0, line.find(" ")));
    *height = stoi(line.substr(line.find(" ") + 1, line.length()));
}

void utils::mapToVector(std::ifstream *file, std::vector<std::vector<int>> *map) {
    std::string line;

    while (getline(*file, line)) {
        std::istringstream iss(line);
        std::vector<int> line;
        int tile;

        while (iss >> tile) {
            line.push_back(tile);
        }

        (*map).push_back(line);
    }
}

int utils::getMax(std::vector<std::vector<int>> vect) {
    int max = vect[0][0];
    
    for (int i = 0; i < vect.size(); i++) {
        for (int j = 0; j < vect[i].size(); j++) {
            if(vect[i][j] > max) {
                max = vect[i][j];
            }
        }
    }

    return max;
    
}

std::string utils::addZeros(int number, int max) {
    int max_length = std::to_string(max).length();
    std::string std_number = std::to_string(number);

    while (std_number.length() < max_length) {
        std_number.insert(0, "0");
    }

    return std_number;
}

bool utils::isInsideVect(int value, std::vector<int> vect) {
    for (int val : vect) {
        if (val == value) {
            return true;
        }
    }
    
    return false;
}

int utils::findIndexById(int id, std::vector<utils::Texture> vect) {

    for (int i = 0; i < vect.size(); i++) {
        if(vect[i].id == id) {
            return i;
        }
    }

    return -1;    
}

utils::TileType utils::getTileTypeByCode(int code) {
    if(code == 0) { return utils::Air; }
    if(code != 0) { return utils::Obstacle; }

    return utils::Error; // It will fire i know
}

bool utils::isColliding(Sprite sprite, std::vector<std::vector<Tile>> map) {

    bool collision = false;

    Rectangle playerRec = {
        sprite.position.x,
        sprite.position.y,
        sprite.width,
        sprite.width
    };

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[j].size(); j++) {
            if (utils::getTileTypeByCode(map[i][j].type) == utils::Obstacle) {
                
                Rectangle obstacle = {
                    (float)(j * TILE_SIZE),
                    (float)(i * TILE_SIZE),
                    sprite.width,
                    sprite.height
                };

                if (CheckCollisionRecs(playerRec, obstacle)) { collision = true; }

            }
        }
    }

    return collision;
    
}