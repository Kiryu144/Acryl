#define ACRYL_STRING_START 'R"('
#define ACRYL_STRING_END ')"'

#include <ctime>
#include <engine/acryl.h>
#include <engine/defaults.h>

int main(int argc, char** argv) {
    srand(time(0));
    Acryl::Window window("Acryl!");

    Acryl::Shader basic("basic.vert", "basic.frag", false);
    Acryl::Shader texture("basic_2d.vert", "basic_2d.frag", false);

    Acryl::Defaults::init();

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
        Acryl::Defaults::Plane_2D->bindVertexAttribArray(0);
        Acryl::Defaults::Plane_2D_UV->bindVertexAttribArray(1);
        glDrawArrays(GL_TRIANGLES, 0, Acryl::Defaults::Plane_2D->getVerticeAmount());

        window.swap();
    }

    return 0;
}