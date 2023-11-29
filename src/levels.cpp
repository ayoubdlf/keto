#include "../include/levels.hpp"

Levels::Levels() {
    this->levels = new Level;
}

Levels::~Levels() {
    // TODO: FREE LEVELS TREE
}

Level* Levels::createLevels(int level = 1, int lastLevel = 1) {
    Level* levels = new Level;

    if(level != MAX_LEVELS + 1) {
        levels->level      = level;
        levels->completed = (level < lastLevel) ? true : false;
        levels->next_level = this->createLevels(level + 1, lastLevel);
    }

    return levels;
}

/*
*   Create levels
*/
void Levels::create() {
    this->levels = this->createLevels();
}

/*
*   Load levels that have akready been created (data.json)
*  `lastLevel` is the last known completed level, 1 if none
*/
void Levels::load(int lastLevel) {
    this->levels = this->createLevels(1, lastLevel);
}

/*
*   'Go' to the next level
*/
void Levels::nextLevel(Level* level) {
    // Tricky, I used this approach to avoid putting manually the parameter value the first time calling this function (inside the game class)
    // If the parameter is null, set the level to the currrent level
    if(level == nullptr) { level = this->levels; } 

    if(level->completed) {
        this->nextLevel(level->next_level);
    } else {
        level->completed = true;
    }
}

/*
*   Get current level map and tiles path
*/
std::string Levels::getCurrentLevelPath(Level* level) {
    // If the parameter is null, set the level to the currrent level
    if(level == nullptr) { level = this->levels; }

    std::string path = "assets/levels/" + std::to_string(level->level) + "/map.txt";;
    
    if(level->completed) {
        path = Levels::getCurrentLevelPath(level->next_level);
    }

    return path;
}

/*
*   Return the current level number
*/
int Levels::getCurrentLevel(Level* level) {
    // Using the same tricky parameter as the others methods
    if(level == nullptr) { level = this->levels; } 

    if(level->completed) {
        return this->getCurrentLevel(level->next_level);
    }

    return level->level;
}
