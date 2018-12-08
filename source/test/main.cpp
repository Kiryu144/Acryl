#include <ctime>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include "../engine/window/window.h"
#include "../engine/opengl/shader/shader.h"
#include "../engine/opengl/vbo/vertexbufferobject.h"
#include "../engine/opengl/texture/texture.h"
#include "../engine/pixelfield/pixelfield.h"
#include "../engine/math/transformation.h"
#include "../engine/math/camera.h"

int main(int argc, char** argv) {
    srand(time(0));
    Acryl::Window window("Acryl!");

    Acryl::Shader basic("basic.vert", "basic.frag", false);
    Acryl::Shader texture("basic_2d.vert", "basic_2d.frag", false);

    glm::vec2 plane[] = {
            glm::vec2(0, 0),
            glm::vec2(1, 0),
            glm::vec2(0, 1),

            glm::vec2(0, 1),
            glm::vec2(1, 1),
            glm::vec2(1, 0)
    };

    glm::vec2 plane_uv[] = {
            glm::vec2(0, 0),
            glm::vec2(1, 0),
            glm::vec2(0, 1),

            glm::vec2(0, 1),
            glm::vec2(1, 1),
            glm::vec2(1, 0)
    };


    Acryl::VertexBufferObject vertices(plane, 12*sizeof(float), 2);
    Acryl::VertexBufferObject uv(plane_uv, 12*sizeof(float), 2);

    Acryl::Transformation transformation(glm::vec3(0, 0, 0), glm::vec3(0), glm::vec3(200, 200, 0));

    Acryl::Texture __texture("./Image1.png");

    Acryl::PixelField field(256, 256);

    for(int r = 0; r <= 255; r++){
        for(int b = 0; b <= 255; b++){
            field.setPixel(r, b, r, 128, b, 128);
        }
    }

    Acryl::Texture anothertexture(field);

    Acryl::Camera camera(Acryl::CameraType::ORTHOGRAPHIC, 0.0, 100.0, 40, Acryl::Transformation(glm::vec3(), glm::vec3(-180, 90, 0), glm::vec3()), window);
    camera.updateMatrices();

    while(!window.quitRequested()){
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        texture.bindProgram();
        anothertexture.bindTexture(0);
        texture.setUniform("sampler", anothertexture.getTextID());
        texture.setUniform("mvp", camera.getProjection() * camera.getView() * transformation.getMatrix());
        vertices.bindVertexAttribArray(0);
        uv.bindVertexAttribArray(1);
        glDrawArrays(GL_TRIANGLES, 0, vertices.getVerticeAmount());

        window.swap();
    }

    return 0;
}