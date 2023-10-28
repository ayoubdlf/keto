#include "../include/camera.hpp"

// Initialize pointer to zero so that it can be initialized in first call to getInstance
CameraSingleton* CameraSingleton::instance = 0;

CameraSingleton::CameraSingleton() {}

CameraSingleton* CameraSingleton::getInstance() {
    if (instance == 0) { instance = new CameraSingleton(); }
    return instance;
}

Camera2D& CameraSingleton::getCamera() { return camera; }