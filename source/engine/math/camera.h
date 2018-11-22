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
    const CameraType mCameraType;
    float mClipNear, mClipFar, mFov, mWidth, mHeigth;
    glm::mat4 mProjection, mView;
    Transformation mTransformation;

public:
    Camera(const CameraType& type, float near, float far, float fov, const Transformation& transformation, const Window& window);
    Camera(const CameraType& type, float near, float far, float fov, const Transformation& transformation, int width, int heigth);

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
