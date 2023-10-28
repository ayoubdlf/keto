#ifndef CAMERA_H
#define CAMERA_H

#include <raylib.h>

class CameraSingleton {
    private:
        Camera2D camera;
        static CameraSingleton* instance;
        CameraSingleton();
    public:
        static CameraSingleton* getInstance();
        Camera2D& getCamera();
};

#endif // CAMERA_H