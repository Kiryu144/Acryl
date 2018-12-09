#ifndef ACRYL_DEFAULTS_H
#define ACRYL_DEFAULTS_H

#include <memory>
#include "opengl/shader/shader.h"
#include "opengl/vbo/vertexbufferobject.h"

namespace Acryl {

namespace Defaults {
    //VBO data
    static glm::vec2 _plane_2D[] =    {glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(0, 1), glm::vec2(0, 1), glm::vec2(1, 1), glm::vec2(1, 0)};
    static glm::vec2 _place_2D_uv[] = {glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(0, 1), glm::vec2(0, 1), glm::vec2(1, 1), glm::vec2(1, 0)};

    //VBOs
    static std::unique_ptr<VertexBufferObject> Plane_2D;
    static std::unique_ptr<VertexBufferObject> Plane_2D_UV;

    //Shader data
    std::string _solid_color_3D_vert =
        #include "opengl/shader/glsl/solid_color_3d.vert"
    ;

    std::string _solid_color_3D_frag =
        #include "opengl/shader/glsl/solid_color_3d.frag"
    ;

    //Shaders
    std::unique_ptr<Shader> SolidColor3D;

    //Init
    static void init() {
        //VBOs
        Plane_2D =    std::unique_ptr<VertexBufferObject>(new VertexBufferObject(_plane_2D, 12*sizeof(float), 2));
        Plane_2D_UV = std::unique_ptr<VertexBufferObject>(new VertexBufferObject(_place_2D_uv, 12*sizeof(float), 2));

        //Shaders
        SolidColor3D = std::unique_ptr<Shader>(new Shader(_solid_color_3D_vert, _solid_color_3D_frag, true));
    }

};

}

#endif
