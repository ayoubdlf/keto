#include "../include/utils.hpp"

namespace utils {

    void mapToVector(std::ifstream *file, std::vector<std::vector<int>> *map) {
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

    bool isInsideVect(int value, std::vector<int> vect) {
        for(int val : vect) {
            if (val == value) {
                return true;
            }
        }
        
        return false;
    }

    int findIndexById(int id, std::vector<CustomTexture> vect) {

        for(int i = 0; i < (int)vect.size(); i++) {
            if(vect[i].id == id) {
                return i;
            }
        }

        return -1;    
    }

    TileType getTileTypeByCode(int code) {
        if(code == 0)              { return Air; }
        if(code == 1)              { return PowerUp_Coin; }
        if(code == 2)              { return PowerUp_Heart; }
        if(code == 3)              { return PowerUp_Bullet; }
        if(code == 4)              { return PowerUp_MedKit; }
        if(code == 5)              { return PowerUp_LuckyBox; }
        if(code == 6)              { return CheckPoint; }
        
        return Obstacle;
    }

    bool isPowerUp(TileType type) {

        if(type == PowerUp_Bullet || type == PowerUp_Coin || type == PowerUp_Heart || type == PowerUp_LuckyBox || type == PowerUp_MedKit) {
            return true;
        }

        return false;
    }

    bool isInsideMap(const std::vector<std::vector<Tile>>& map, int x, int y) {
        return (y >= 0 && y < (int)map.size() && x >= 0 && x < (int)map[y].size());
    }
}
