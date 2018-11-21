#include "../engine/window/window.h"
#include "../engine/opengl/shader/glshadercompiler.h"
#include "../engine/opengl/vbo/vertexbufferobject.h"


int main(int argc, char** argv) {
    Acryl::Window window("Acryl!");

    Acryl::GLShaderCompiler shaderCompiler("basic123.vert", "basic.frag", false);
    GLuint programID = shaderCompiler.compileAndLink();

    float dummyData[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    Acryl::VertexBufferObject dummyVBO(dummyData, 9*sizeof(float));

    while(!window.quitRequested()){
        window.swap();
    }

    return 0;
}