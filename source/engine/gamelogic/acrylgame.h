#ifndef ACRYL_ACRYLGAME_H
#define ACRYL_ACRYLGAME_H

#include <chrono>

#include "../math/camera.h"
#include "../window/window.h"
#include "../defaults.h"

namespace Acryl {

class AcrylGame : public Listener {
private:
    std::chrono::high_resolution_clock::time_point m_lastTime;
protected:
    Window m_window;
    Camera m_camera;

    double m_deltaTime;

    AcrylGame(const std::string& title, int width, int height);
    void start();
    double getFPS();
public:
    virtual void update() = 0;
};

}

#endif
