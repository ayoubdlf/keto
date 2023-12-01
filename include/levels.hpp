#ifndef LEVELS_HPP
#define LEVELS_HPP

#include <iostream>
#include "utils.hpp"

using namespace utils;

struct Level {
    int  level        = 1;
    bool completed    = false;
    Level* next_level = nullptr;
};

class Levels {
    private:
        Level* levels;
        Level* createLevels(int level, int lastLevel);
    public:
        Levels();
        ~Levels();
        void create();
        void load();
        void nextLevel(Level* level = nullptr);
        std::string getCurrentLevelPath(Level* level = nullptr);
        int getCurrentLevel(Level* level = nullptr);
        bool isLastLevel();
};


#endif // LEVELS_HPP
