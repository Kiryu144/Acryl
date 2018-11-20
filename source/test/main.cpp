#include "../engine/window/window.h"
#include "../engine/shader/glshadercompiler.h"


int main(int argc, char** argv) {
    Acryl::Window window("Acryl!");

    Acryl::GLShaderCompiler shaderCompiler("chunk.vert", "chunk.frag", false);
    GLuint programID = shaderCompiler.compileAndLink();



    return 0;
}