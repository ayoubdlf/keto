#include "../include/camera.hpp"


CameraSingleton* CameraSingleton::getInstance() {
    if (instance == 0) { instance = new CameraSingleton(); }
    return instance;
}

Camera2D& CameraSingleton::getCamera() {
    return this->camera;
}

CameraSingleton* CameraSingleton::instance = 0;
