#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <raylib.h>
#include "utils.hpp"

using namespace utils;

class Map {
    private:
        static Map* instance;
        
        std::vector<std::vector<int>> map;
        std::vector<std::vector<Tile>> tilesMap;
        std::vector<Tile> obstacles;
        std::vector<utils::Texture> textures;

        void loadTiles();
    public:
        ~Map();

        static Map* getInstance();
        std::vector<Tile>& getObstacles();
        
        void load(std::string filepath);
        void loadTextures();
        void draw();
};


#endif // MAP_HPP
