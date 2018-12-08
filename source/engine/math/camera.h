#ifndef ACRYL_CAMERA_H
#define ACRYL_CAMERA_H

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include "transformation.h"
#include "../window/window.h"


namespace Acryl {

enum class CameraType : char {
    PERSPECTIVE,
    ORTHOGRAPHIC
};

class Camera {
protected:
    const CameraType m_cameraType;
    float m_clipNear, m_clipFar, m_fov, m_width, m_height;
    glm::mat4 m_projection, m_view;
    Transformation m_transformation;

public:
    Camera(const CameraType& type, float near, float far, float fov, const Transformation& transformation, const Window& window);
    Camera(const CameraType& type, float near, float far, float fov, const Transformation& transformation, int width, int height);

    void updateMatrices();

    const CameraType getCameraType() const;
    float getClipNear() const;
    float getClipFar() const;
    float getFov() const;
    const glm::mat4& getProjection() const;
    const glm::mat4& getView() const;
    Transformation& getTransformation();

    void setClipNear(float clipNear);
    void setClipFar(float clipFar);
    void setFov(float fov);
};

}

#endif
