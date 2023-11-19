#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <raylib.h>
#include <vector>
#include <cstring>
#include <cmath>

//  START DEFINES
constexpr int   WIDTH            =   960;
constexpr int   HEIGHT           =   560;
constexpr float SCALE            =   100.0f;
constexpr float DELTA            =   0.01f;
constexpr float GRAVITY          =   80.0f * DELTA;
constexpr float X_VELOCITY       =   5.0f;
constexpr float Y_VELOCITY       =   X_VELOCITY * 2.8;
constexpr float ZOOM             =   1.2f;
constexpr int   X_FRAME_SPEED    =   12;
constexpr int   Y_FRAME_SPEED    =   X_FRAME_SPEED * 2;
constexpr int   MAX_BULLETS      =   20000;
constexpr float BULLET_VELOCITY  =   8.0f;
//  END DEFINES


namespace utils {

    enum Direction {
        Left  = 0,
        Right = 1
    };
        
    enum TileType {
        Air = 0,
        Obstacle = 1,
        Error = -1
    };

    struct Tile {
        Texture2D texture;
        Vector2 pos;
        utils::TileType type;
    };

    struct Texture {
        int id;
        Texture2D texture;
    };
    
    /*
    *   Saves map file data to vector
    */
    void mapToVector(std::ifstream *file, std::vector<std::vector<int>> *map);

    /*
    *   Get max value inside a 2d vector
    */
    int getMax(std::vector<std::vector<int>> vect);

    /*
    *   Number should have same length as max
    *   Example:
    *       input : number=1, max=123
    *       output: 001
    */
    std::string addZeros(int number, int max);

    /*
    *   Returns if value is inside the vector `vect`
    */
    bool isInsideVect(int value, std::vector<int> vect);

    /*
    *   Finds in which index `id` is, -1 otherwise
    */
    int findIndexById(int id, std::vector<utils::Texture> textureVect);

    /*
    *   Get value in map // TODO: comment in a clear way
    */
    utils::TileType getTileTypeByCode(int code);
}


#endif // UTILS_HPP
