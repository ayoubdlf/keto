#include "../include/camera.hpp"


CameraSingleton* CameraSingleton::getInstance() {
    if (instance == nullptr) { instance = new CameraSingleton(); }
    return instance;
}

Camera2D& CameraSingleton::getCamera() {
    return this->camera;
}

CameraSingleton* CameraSingleton::instance = nullptr;
