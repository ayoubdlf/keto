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
        /* Map */
        std::vector<std::vector<int>> map;
        std::vector<std::vector<Tile>> tilesMap;
        Tile checkPoint;
        std::vector<Tile> obstacles;
        std::vector<Tile> powerUps;
        std::vector<CustomTexture> textures;

        std::string mapPath;
        int mapWidth;
        int mapHeight;
        
        float tileWidth;
        float tileHeight;
        
        /* Tiles that aren't static, meaning they can move (powerUps in out case) */
        int framesCounter;
        int framesSpeed;

        void loadTiles();
        CustomTexture loadCustomTexture(int id, std::string path, std::string custom);
    public:
        Map();
        ~Map();
        std::vector<std::vector<int>>& getMap();
        std::vector<std::vector<Tile>>& getTilesMap();
        std::vector<Tile>& getPowerUps();
        Tile getCheckPoint();
        std::vector<Tile>& getObstacles();
        void load(std::string filepath);
        void drawPowerUps();
        void draw();
        void update();
        void usePowerUp(int i);
        int getWidth();
        int getHeight();
        void loadTextures();
        void reset();
};


#endif // MAP_HPP
