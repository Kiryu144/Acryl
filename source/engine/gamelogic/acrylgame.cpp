#include "acrylgame.h"

namespace Acryl {

AcrylGame::AcrylGame(const std::string& title, int width, int height)
    : m_window(title, width, height),
      m_camera(CameraType::ORTHOGRAPHIC, 0.0, 100.0, 40, Acryl::Transformation(glm::vec3(), glm::vec3(-180, 90, 0), glm::vec3()), m_window) {
    Acryl::Defaults::init();
    m_camera.updateMatrices();
    m_lastTime = std::chrono::high_resolution_clock::now();
}

void AcrylGame::start() {
    while(!m_window.quitRequested()){
        m_window.swap();
        glClearColor(0.0f, 0.1f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        auto curr = std::chrono::high_resolution_clock::now();
        m_deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(curr - m_lastTime).count() / 1000.0;
        m_lastTime = curr;

        update();
    }
}

double AcrylGame::getFPS() {
    return 1000.0f / m_deltaTime;
}

}