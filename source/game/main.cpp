#include <engine/acryl.h>

int main(int argc, char** argv) {
    Acryl::Window window("Acryl");

    Acryl::Defaults::init();

    Acryl::Camera camera(Acryl::CameraType::ORTHOGRAPHIC, 0.0, 100.0, 40, Acryl::Transformation(glm::vec3(), glm::vec3(-180, 90, 0), glm::vec3()), window);
    camera.updateMatrices();

    Acryl::Transformation imageTransformation(glm::vec3(0, 0, 0), glm::vec3(0), glm::vec3(200, 200, 0));

    while(!window.quitRequested()){
        window.swap();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        /*
        Acryl::Defaults::Texture2D->bindProgram();
        Acryl::Defaults::DebugTexture->bindTexture(0);

        Acryl::Defaults::Texture2D->setUniform("sampler", Acryl::Defaults::DebugTexture->getTextID());
        Acryl::Defaults::Texture2D->setUniform("mvp", camera.getProjection() * camera.getView() * imageTransformation.getMatrix());

        Acryl::Defaults::Plane_2D->bindVertexAttribArray(0);
        Acryl::Defaults::Plane_2D_UV->bindVertexAttribArray(1);

        glDrawArrays(GL_TRIANGLES, 0, Acryl::Defaults::Plane_2D->getVerticeAmount());
         */
    }

    return 0;
}