#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <raylib.h>
#include "utils.hpp"

using namespace utils;


namespace menuType {
    enum type {
        Welcome = 0,
        LevelSelection  = 1,
    };
};


class Menu {

    private:

    std::vector<Texture2D> textures;
    menuType::type menuType;

    public:
    
    Menu();
      ~Menu();
    
    void drawMenu();
    void loadTexture();







}













#endif // MENU_HPP