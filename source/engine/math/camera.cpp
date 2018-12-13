#include "camera.h"


namespace Acryl {

/**
 * @param type Projection type. Used for the projection matrix calculations.
 * @param near Near clipping
 * @param far Far clipping
 * @param fov The field of view. Should normally be between 60 and 120
 * @param transformation Camera transformation
 * @param window The window to gather the width and heigth from
 */
Camera::Camera(const CameraType& type, float near, float far, float fov, const Transformation& transformation, const Window& window)
    : m_cameraType(type), m_clipNear(near), m_clipFar(far), m_fov(fov), m_transformation(transformation), m_width(window.getWidth()), m_height(window.getHeigth()) {
    updateMatrices();
}

/**
 * @param type Projection type. Used for the projection matrix calculations.
 * @param near Near clipping
 * @param far Far clipping
 * @param fov The field of view. Should normally be between 60 and 120
 * @param transformation Camera transformation
 * @param width The width the screen is the camera is in
 * @param width The heigth the screen is the camera is in
 */
Camera::Camera(const CameraType& type, float near, float far, float fov, const Transformation& transformation, int width, int height)
    : m_cameraType(type), m_clipNear(near), m_clipFar(far), m_fov(fov), m_transformation(transformation), m_width(width), m_height(height) {
    updateMatrices();
}

/**
 * @brief Updates the projection and the view matrix
 */
void Camera::updateMatrices() {
    switch(m_cameraType){
        case CameraType::ORTHOGRAPHIC: m_projection = glm::ortho(0.0f, m_width, m_height, 0.0f, m_clipNear, m_clipFar); break;
        case CameraType::PERSPECTIVE:  m_projection = glm::perspective(glm::radians(m_fov), m_width/m_height, m_clipNear, m_clipFar);  break;
    }

    glm::vec3 front;
    front.x = std::cos(glm::radians(m_transformation.getRotation().x)) * std::cos(glm::radians(m_transformation.getRotation().y));
    front.y = std::sin(glm::radians(m_transformation.getRotation().x));
    front.z = std::cos(glm::radians(m_transformation.getRotation().x)) * std::sin(glm::radians(m_transformation.getRotation().y));

    m_view = glm::lookAt(m_transformation.getPosition(), m_transformation.getPosition() + front, glm::vec3(0.0f, 1.0f, 0.0f));
}

const CameraType Camera::getCameraType() const {
    return m_cameraType;
}

float Camera::getClipNear() const {
    return m_clipNear;
}

float Camera::getClipFar() const {
    return m_clipFar;
}

float Camera::getFov() const {
    return m_fov;
}

const glm::mat4& Camera::getProjection() const {
    return m_projection;
}

const glm::mat4& Camera::getView() const {
    return m_view;
}

Transformation& Camera::getTransformation() {
    return m_transformation;
}

void Camera::setClipNear(float clipNear) {
    m_clipNear = clipNear;
}

void Camera::setClipFar(float clipFar) {
    m_clipFar = clipFar;
}

void Camera::setFov(float fov) {
    m_fov = fov;
}


}