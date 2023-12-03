#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <raylib.h>
#include <vector>
#include <cstring>
#include <cmath>
#include <nlohmann/json.hpp>
#include <filesystem>

using json   = nlohmann::json;
namespace fs = std::filesystem;

//  START DEFINES
constexpr int   WIDTH            =   960;
constexpr int   HEIGHT           =   560;
constexpr float SCALE            =   100.0f;
constexpr float DELTA            =   0.01f;
constexpr float GRAVITY          =   80.0f * DELTA;
constexpr float X_VELOCITY       =   5.0f;
constexpr float Y_VELOCITY       =   X_VELOCITY * 2.8;
constexpr float ZOOM             =   1.5f;
constexpr int   X_FRAME_SPEED    =   12;
constexpr int   Y_FRAME_SPEED    =   X_FRAME_SPEED * 2;
constexpr int   MAX_BULLETS      =   30;
constexpr float BULLET_VELOCITY  =   8.0f;
constexpr int   NB_ENEMIES       =   10;
constexpr int   MAX_HEALTH       =   10;
constexpr int   MAX_LEVELS       =   2;
//  END DEFINES

namespace utils {

    enum state {
        Start      = 0,
        GameOver   = 1,
        Playing    = 2,
        Pause      = 3,
        Skins      = 4,
        Completed  = 5,
        Exit       = 6
    };

    struct AlertMessage {
        int time;
        bool active;
        Vector2 position;
        std::string message;
    };

    // CustomTexture refers to a texture(spritesheet) that can possibly move
    // By moving a mean drawing portioins of this texture(spritesheet) at a time
    struct CustomTexture {
        int id;
        Texture2D texture;
        Rectangle frames;
    };
    
    namespace shooter {
        enum type {
            Player = 0,
            Enemy  = 1,
        };
    };
    
    enum Direction {
        Left  = 0,
        Right = 1
    };

    enum TileType {
        Air              = 0,
        Obstacle         = 1,
        
        PowerUp_Bullet   = 2,
        PowerUp_Coin     = 3,
        PowerUp_Heart    = 4,
        PowerUp_MedKit   = 5,
        PowerUp_LuckyBox = 6,
        CheckPoint = 7,
    };

    struct Tile {
        Texture2D texture;
        Vector2 pos;
        TileType type;
        Rectangle frames;
        int currentFrame;
    };
    
    /*
    *   Saves map file data to vector
    */
    void mapToVector(std::ifstream *file, std::vector<std::vector<int>> *map);

    /*
    *   Returns if value is inside the vector `vect`
    */
    bool isInsideVect(int value, std::vector<int> vect);

    /*
    *   Finds in which index `id` is, -1 otherwise
    */
    int findIndexById(int id, std::vector<CustomTexture> textureVect);

    /*
    *   Get value in map
    */
    TileType getTileTypeByCode(int code);

    /*
    *   Check if tile is a powerUp
    */
    bool isPowerUp(TileType type);

    /*
    *   Check if (x, y) coordonates are inside the map
    */
    bool isInsideMap(const std::vector<std::vector<Tile>>& map, int x, int y);
}

#endif // UTILS_HPP
