#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <fstream>
#include <cassert>
#include <raylib.h>
#include "utils.hpp"

using namespace utils;

class Map {
    private:        
        std::vector<std::vector<int>> map;
        std::vector<std::vector<Tile>> tilesMap;
        std::vector<Tile> obstacles;
        std::vector<utils::Texture> textures;

        void loadTiles();
    public:
        ~Map();
        std::vector<Tile>& getObstacles();
        void load(std::string filepath);
        void loadTextures();
        void draw();
};


#endif // MAP_HPP
