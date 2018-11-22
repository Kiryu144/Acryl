#ifndef ACRYL_CAMERA_H
#define ACRYL_CAMERA_H

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include "transformation.h"


namespace Acryl {

enum class CameraType : char {
    PERSPECTIVE,
    ORTHOGRAPHIC
};

class Camera {
protected:
    const CameraType mCameraType;
    float mClipNear, mClipFar, mFov;
    glm::mat4 mProjection, mView;
    Transformation mTransformation;


public:
    Camera(const CameraType& type, float near, float far, float fov, const Transformation& transformation);

    void updateMatrices(float width, float heigth);

    const CameraType getCameraType() const;
    float getClipNear() const;
    float getClipFar() const;
    float getFov() const;
    const glm::mat4& getProjection() const;
    const glm::mat4& getView() const;
    const Transformation& getTransformation() const;

    void setClipNear(float clipNear);
    void setClipFar(float clipFar);
    void setFov(float fov);
    void setTransformation(const Transformation& transformation);
};

}

#endif
