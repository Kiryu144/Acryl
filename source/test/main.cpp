#include "../engine/window/window.h"
#include "../engine/opengl/shader/shader.h"
#include "../engine/opengl/vbo/vertexbufferobject.h"
#include "../engine/opengl/texture/texture.h"
#include "../engine/math/transformation.h"
#include "../engine/math/camera.h"


int main(int argc, char** argv) {
    Acryl::Window window("Acryl!");

    Acryl::Shader basic("basic.vert", "basic.frag", false);
    Acryl::Shader texture("texture.vert", "texture.frag", false);

    glm::vec3 plane[] = {
            glm::vec3(0, 0, 0),
            glm::vec3(1, 0, 0),
            glm::vec3(0, 1, 0),

            glm::vec3(0, 1, 0),
            glm::vec3(1, 1, 0),
            glm::vec3(1, 0, 0)
    };

    glm::vec2 plane_uv[] = {
            glm::vec2(0, 0),
            glm::vec2(1, 0),
            glm::vec2(0, 1),

            glm::vec2(0, 1),
            glm::vec2(1, 1),
            glm::vec2(1, 0)
    };


    Acryl::VertexBufferObject dummyVBO(plane, 18*sizeof(float), 3);
    Acryl::VertexBufferObject vertices(plane, 18*sizeof(float), 3);
    Acryl::VertexBufferObject uv(plane_uv, 12*sizeof(float), 2);

    Acryl::Transformation transformation(glm::vec3(0, 0, 0), glm::vec3(0), glm::vec3(1));

    Acryl::Texture __texture("./Image1.png");

    Acryl::Camera camera(Acryl::CameraType::PERSPECTIVE, 0.001, 100.0, 40, Acryl::Transformation(glm::vec3(0, 0, -1.2)));
    camera.updateMatrices(window.getWidth(), window.getHeigth());

    while(!window.quitRequested()){
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        texture.bindProgram();
        __texture.bindTexture(0);
        texture.setUniform("sampler", __texture.getTextID());
        texture.setUniform("mvp", camera.getProjection() * camera.getView() * transformation.getMatrix());
        vertices.bindVertexAttribArray(0);
        uv.bindVertexAttribArray(1);
        glDrawArrays(GL_TRIANGLES, 0, vertices.getVerticeAmount());


        window.swap();
    }

    return 0;
}