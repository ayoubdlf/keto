#include "../include/utils.hpp"

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

bool utils::isInsideVect(int value, std::vector<int> vect) {
    for(int val : vect) {
        if (val == value) {
            return true;
        }
    }
    
    return false;
}

int utils::findIndexById(int id, std::vector<utils::CustomTexture> vect) {

    for(int i = 0; i < (int)vect.size(); i++) {
        if(vect[i].id == id) {
            return i;
        }
    }

    return -1;    
}

utils::TileType utils::getTileTypeByCode(int code) {
    if(code == 0)              { return utils::Air; }
    if(code == 1)              { return utils::PowerUp_Coin; }
    if(code == 2)              { return utils::PowerUp_Heart; }
    if(code == 3)              { return utils::PowerUp_Bullet; }
    if(code == 4)              { return utils::PowerUp_MedKit; }
    if(code == 5)              { return utils::PowerUp_LuckyBox; }
    
    return utils::Obstacle;
}

bool utils::isPowerUp(utils::TileType type) {

    if(type == PowerUp_Bullet || type == PowerUp_Coin || type == PowerUp_Heart || type == PowerUp_LuckyBox || type == PowerUp_MedKit ) {
        return true;
    }

    return false;
}
