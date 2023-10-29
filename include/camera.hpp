#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <raylib.h>

class CameraSingleton {
    private:
        Camera2D camera;
        static CameraSingleton* instance;
    public:
        static CameraSingleton* getInstance();
        Camera2D& getCamera();
};

#endif // CAMERA_HPP