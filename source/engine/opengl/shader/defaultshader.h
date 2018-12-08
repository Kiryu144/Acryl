#ifndef ACRYL_DEFAULTSHADER_H
#define ACRYL_DEFAULTSHADER_H

#include <string>
#include <memory>

#include "shader.h"

namespace Acryl {

std::string solid_color_3d_vert =
    #include "glsl/solid_color_3d.vert"
;

std::string solid_color_3d_frag =
    #include "glsl/solid_color_3d.frag"
;

namespace DefaultShader{
    std::unique_ptr<Shader> SolidColor3D;

    void init() {
        SolidColor3D = std::unique_ptr<Shader>(new Shader(solid_color_3d_vert, solid_color_3d_frag, true));

    }
};

}

#endif //ACRYL_DEFAULTSHADER_H
