#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <raylib.h>

//  START DEFINES
#define WIDTH 640
#define HEIGHT 320
#define TILE_SIZE 32
#define MAP_WIDTH (WIDTH/TILE_SIZE)
#define MAP_HEIGHT (HEIGHT/TILE_SIZE)
//  END DEFINES

namespace utils {

    // struct Position {
    //     int x;
    //     int y;
    // };

    struct Tile {
        Texture2D texture;
        Vector2 pos;
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
}


#endif // UTILS_HPP
