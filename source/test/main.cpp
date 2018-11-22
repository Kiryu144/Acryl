#include "../engine/window/window.h"
#include "../engine/opengl/shader/shader.h"
#include "../engine/opengl/vbo/vertexbufferobject.h"
#include "../engine/opengl/texture/texture.h"
#include "../engine/math/transformation.h"
#include "../engine/math/camera.h"

int main(int argc, char** argv) {
    Acryl::Window window("Acryl!");

    while(!window.quitRequested()){
        window.swap();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

    }

    return 0;
}