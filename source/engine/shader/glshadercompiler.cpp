#include "glshadercompiler.h"

namespace Acryl {

/**
 * @param vertex The vertex shader source or path depending on 'isSource'
 * @param fragment The fragment shader source or path depending on 'isSource'
 * @param isSource Specifies if the supplied variables are source-code or a path
 */
GLShaderCompiler::GLShaderCompiler(const std::string& vertex, const std::string& fragment, bool isSource) {
    if(!isSource){ //A path is provided
        try{
            readFileToBuffer(vertex, mVertexShader);
        }catch(const std::ifstream::failure& e){
            std::cerr << "Could not read vertex file " << vertex << std::endl;
        }

        try{
            readFileToBuffer(fragment, mFragmentShader);
        }catch(const std::ifstream::failure& e){
            std::cerr << "Could not read fragment file " << vertex << std::endl;
        }
    }
}

/**
 * @param vertex The vertex shader source or path depending on 'isSource'
 * @param fragment The fragment shader source or path depending on 'isSource'
 * @param geometry The geometry shader source or path depending on 'isSource'
 * @param isSource Specifies if the supplied variables are source-code or a path
 */
GLShaderCompiler::GLShaderCompiler(const std::string& vertex, const std::string& fragment, const std::string& geometry, bool isSource) {
    if(!isSource){ //A path is provided
        try{
            readFileToBuffer(vertex, mVertexShader);
        }catch(const std::ifstream::failure& e){
            std::cerr << "Could not read vertex file " << vertex << std::endl;
        }

        try{
            readFileToBuffer(fragment, mFragmentShader);
        }catch(const std::ifstream::failure& e){
            std::cerr << "Could not read fragment file " << vertex << std::endl;
        }

        try{
            readFileToBuffer(geometry, mGeometryShader);
        }catch(const std::ifstream::failure& e){
            std::cerr << "Could not read geometry file " << vertex << std::endl;
        }
    }
}


/**
 * @param type The type of shader to be compiled. eg. GL_FRAGMENT_SHADER
 * @param src The source code of the shader
 * @return The program-id of the given shader
 */
GLuint GLShaderCompiler::compileShader(GLenum type, const std::string& src) const {
    GLuint shaderID = glCreateShader(type);

    const char* c_str = src.c_str();
    glShaderSource(shaderID, 1, &c_str, nullptr);
    glCompileShader(shaderID);

    GLint success = GL_FALSE;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        GLint logLenght = 0;
        char* log;

        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLenght);
        log = new char[logLenght];
        glGetShaderInfoLog(shaderID, logLenght, &logLenght, &log[0]);
        glDeleteShader(shaderID);

        std::string shaderType;
        switch (type) {
            case GL_VERTEX_SHADER:
                shaderType = "GL_VERTEX_SHADER";
                break;
            case GL_FRAGMENT_SHADER:
                shaderType = "GL_FRAGMENT_SHADER";
                break;
            case GL_GEOMETRY_SHADER:
                shaderType = "GL_GEOMETRY_SHADER";
                break;
            default:
                shaderType = "UNKNOWN";
                break;
        }

        throw std::invalid_argument("Could not compile " + shaderType + "\n" + std::string(log));
    }

    return shaderID;
}


/***
 * @brief Every program-id that is zero will be ignored for linking
 * @param vertex The vertex program-id generated by compileShader(GL_VERTEX_SHADER, ..)
 * @param fragment The fragment program-id generated by compileShader(GL_VERTEX_SHADER, ..)
 * @param geometry The geometry program-id generated by compileShader(GL_VERTEX_SHADER, ..)
 * @return The programID supplied by the GPU
 */
GLuint GLShaderCompiler::linkShader(GLuint vertex, GLuint fragment, GLuint geometry) const {
    GLuint programID = glCreateProgram();

    if (vertex != 0) {
        glAttachShader(programID, vertex);
    }

    if (fragment != 0) {
        glAttachShader(programID, fragment);
    }

    if (geometry != 0) {
        glAttachShader(programID, geometry);
    }

    glLinkProgram(programID);

    GLint isLinked = 0;
    glGetProgramiv(programID, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE) {
        GLint logLenght;
        std::string log;

        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLenght);
        log.reserve(logLenght);
        glGetProgramInfoLog(programID, logLenght, &logLenght, &log[0]);
        glDeleteProgram(programID);

        throw std::invalid_argument("Could not link shaders!\n" + std::string(log));
    }

    glDetachShader(programID, vertex);
    glDetachShader(programID, fragment);
    glDetachShader(programID, geometry);

    return programID;
}

/**
 * @return The programID supplied by the GPU
 */
GLuint GLShaderCompiler::compileAndLink() const {
    GLuint vertexShader   = (!mVertexShader.empty())   ? compileShader(GL_VERTEX_SHADER,   mVertexShader)   : 0;
    GLuint fragmentShader = (!mFragmentShader.empty()) ? compileShader(GL_FRAGMENT_SHADER, mFragmentShader) : 0;
    GLuint geometryShader = (!mGeometryShader.empty()) ? compileShader(GL_GEOMETRY_SHADER, mGeometryShader) : 0;

    return linkShader(vertexShader, fragmentShader, geometryShader);
}

}
