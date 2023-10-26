#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <raylib.h>

//  START DEFINES
#define WIDTH          640
#define HEIGHT         320
#define TILE_SIZE      32
#define SCALE          100.0f
#define DELTA          0.01
#define GRAVITY        80.0f * DELTA
#define X_VELOCITY     5.0f
#define Y_VELOCITY     X_VELOCITY * 2.8
#define ZOOM           1.2f
#define X_FRAME_SPEED  12
#define Y_FRAME_SPEED  X_FRAME_SPEED * 2
//  END DEFINES

namespace utils {
    
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
    *   Gets map width and height
    */
    void getMapSize(std::ifstream *file, int *width, int *height);
    
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
