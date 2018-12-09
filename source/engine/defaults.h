#ifndef ACRYL_DEFAULTS_H
#define ACRYL_DEFAULTS_H

#include <memory>
#include "opengl/shader/shader.h"
#include "opengl/vbo/vertexbufferobject.h"
#include "opengl/texture/texture.h"
#include "pixelfield/pixelfield.h"

namespace Acryl {

namespace Defaults {
    //VBO data
    static glm::vec2 _plane_2D[] =    {glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(0, 1), glm::vec2(0, 1), glm::vec2(1, 1), glm::vec2(1, 0)};
    static glm::vec2 _place_2D_uv[] = {glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(0, 1), glm::vec2(0, 1), glm::vec2(1, 1), glm::vec2(1, 0)};

    //VBOs
    static std::unique_ptr<VertexBufferObject> Plane_2D;
    static std::unique_ptr<VertexBufferObject> Plane_2D_UV;

    //Shader data
    static std::string _solid_color_3D_vert =
        #include "opengl/shader/glsl/solid_color_3d.vert"
    ;

    static std::string _solid_color_3D_frag =
        #include "opengl/shader/glsl/solid_color_3d.frag"
    ;

    static std::string _texture_2D_vert =
        #include "opengl/shader/glsl/texture_2d.vert"
    ;

    static std::string _texture_2D_frag =
        #include "opengl/shader/glsl/texture_2d.frag"
    ;

    static std::string _i_texture_2D_vert =
        #include "opengl/shader/glsl/i_texture_2d.vert"
    ;

    static std::string _i_texture_2D_frag =
        #include "opengl/shader/glsl/i_texture_2d.frag"
    ;

    //Shaders
    static std::unique_ptr<Shader> SolidColor3D;
    static std::unique_ptr<Shader> Texture2D;
    static std::unique_ptr<Shader> iTexture2D;

    //Texture data
    static PixelField _debugTexturePixelField(2, 2);

    //Textures
    static std::unique_ptr<Texture> DebugTexture;

    //Init
    static bool _alreadyInitialized = false;
    static void init() {
        if(_alreadyInitialized) return;
        else _alreadyInitialized = true;

        //VBOs
        Plane_2D =    std::unique_ptr<VertexBufferObject>(new VertexBufferObject(_plane_2D, 12*sizeof(float), 2));
        Plane_2D_UV = std::unique_ptr<VertexBufferObject>(new VertexBufferObject(_place_2D_uv, 12*sizeof(float), 2));

        //Shaders
        SolidColor3D = std::unique_ptr<Shader>(new Shader(_solid_color_3D_vert, _solid_color_3D_frag, true));
        Texture2D =    std::unique_ptr<Shader>(new Shader(_texture_2D_vert, _texture_2D_frag, true));
        iTexture2D =   std::unique_ptr<Shader>(new Shader(_i_texture_2D_vert, _i_texture_2D_frag, true));

        //Textures
        _debugTexturePixelField.setPixel(0, 0, 255, 0, 255, 255);
        _debugTexturePixelField.setPixel(1, 0, 0, 0, 0, 255);
        _debugTexturePixelField.setPixel(0, 1, 0, 0, 0, 255);
        _debugTexturePixelField.setPixel(1, 1, 255, 0, 255, 255);
        DebugTexture = std::unique_ptr<Texture>(new Texture(_debugTexturePixelField));
    }

};

}

#endif
