#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <raylib.h>
#include "utils.hpp"

using namespace utils;

class Map {
    private:
        int width; // nb of tiles in x axis
        int height; // nb of tiles in y axis
        std::vector<std::vector<int>> map;
        std::vector<std::vector<Tile>> tilesMap;
        std::vector<Tile> obstacles;
        std::vector<utils::Texture> textures;
        void loadTiles();
    public:
        Map();
        ~Map();
        void load(std::string filepath);
        void loadTextures();
        void unloadTextures();
        void draw();
        // std::vector<std::vector<Tile>> *getMap();
        std::vector<Tile> *getObstacle();
};


#endif // MAP_HPP
