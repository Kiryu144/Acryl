#include "../engine/window/window.h"
#include "../engine/opengl/shader/glshadercompiler.h"
#include "../engine/opengl/vbo/vertexbufferobject.h"


int main(int argc, char** argv) {
    Acryl::Window window("Acryl!");

    Acryl::GLShaderCompiler shaderCompiler("basic.vert", "basic.frag", false);
    GLuint programID = shaderCompiler.compileAndLink();

    float dummyData[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    Acryl::VertexBufferObject dummyVBO(dummyData, 9*sizeof(float));
    while(!window.quitRequested()){
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(programID);
        dummyVBO.bindVertexAttribArray(0);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.swap();
    }

    return 0;
}