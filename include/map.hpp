#pragma once
#include <iostream>
#include <raylib.h>
#include "utils.hpp"

class Map {
    private:
        std::vector<std::vector<int>> map;
        std::vector<std::vector<utils::Tile>> tilesMap;
        int width; // nb of tiles in x axis
        int height; // nb of tiles in y axis
        std::vector<utils::Texture> textures;
        void loadTiles();
    public:
        Map();
        ~Map();
        void load(std::string filepath);
        void loadTextures();
        void unloadTextures();
        void draw();
};
