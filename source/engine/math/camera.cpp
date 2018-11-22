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
    : mCameraType(type), mClipNear(near), mClipFar(far), mFov(fov), mTransformation(transformation), mWidth(window.getWidth()), mHeigth(window.getHeigth()) {
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
Camera::Camera(const CameraType& type, float near, float far, float fov, const Transformation& transformation, int width, int heigth)
    : mCameraType(type), mClipNear(near), mClipFar(far), mFov(fov), mTransformation(transformation), mWidth(width), mHeigth(heigth) {
    updateMatrices();
}

/**
 * @brief Updates the projection and the view matrix
 */
void Camera::updateMatrices() {
    switch(mCameraType){
        case CameraType::ORTHOGRAPHIC: mProjection = glm::ortho(0.0f, mWidth, mHeigth, 0.0f, mClipNear, mClipFar); break;
        case CameraType::PERSPECTIVE:  mProjection = glm::perspective(glm::radians(mFov), mWidth/mHeigth, mClipNear, mClipFar);  break;
    }

    glm::vec3 front;
    front.x = std::cos(glm::radians(mTransformation.getRotation().x)) * std::cos(glm::radians(mTransformation.getRotation().y));
    front.y = std::sin(glm::radians(mTransformation.getRotation().x));
    front.z = std::cos(glm::radians(mTransformation.getRotation().x)) * std::sin(glm::radians(mTransformation.getRotation().y));

    mView = glm::lookAt(mTransformation.getPosition(), mTransformation.getPosition() + front, glm::vec3(0.0f, 1.0f, 0.0f));
}

const CameraType Camera::getCameraType() const {
    return mCameraType;
}

float Camera::getClipNear() const {
    return mClipNear;
}

float Camera::getClipFar() const {
    return mClipFar;
}

float Camera::getFov() const {
    return mFov;
}

const glm::mat4& Camera::getProjection() const {
    return mProjection;
}

const glm::mat4& Camera::getView() const {
    return mView;
}

Transformation& Camera::getTransformation() {
    return mTransformation;
}

void Camera::setClipNear(float clipNear) {
    mClipNear = clipNear;
}

void Camera::setClipFar(float clipFar) {
    mClipFar = clipFar;
}

void Camera::setFov(float fov) {
    mFov = fov;
}


}