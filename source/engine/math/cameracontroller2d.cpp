#include "cameracontroller2d.h"

Acryl::CameraController2D::CameraController2D(Acryl::Camera& camera)
    : m_camera(camera) {

}

void Acryl::CameraController2D::update(const double& delta) {
    const Uint8* state = SDL_GetKeyboardState(nullptr);

    if(state[SDL_SCANCODE_W]){
        m_camera.getTransformation().setPosition(m_camera.getTransformation().getPosition() + glm::vec3(20 * delta, 0, 0));
    }

}
