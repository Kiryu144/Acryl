#ifndef ACRYL_CAMERACONTROLLER2D_H
#define ACRYL_CAMERACONTROLLER2D_H

#include "camera.h"

namespace Acryl {

class CameraController2D {
private:
    Camera& m_camera;
public:
    CameraController2D(Camera& camera);

    void update(const double& delta);
};

}

#endif
