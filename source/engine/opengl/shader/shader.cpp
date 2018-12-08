#include "shader.h"

namespace Acryl {

/**
 * @brief Is used to prevent a new bind() call when the current shader is still bound
 */
GLuint Shader::lastBoundProgramID = 0;

/**
 * @param vertex The vertex shader source or path depending on 'isSource'
 * @param fragment The fragment shader source or path depending on 'isSource'
 * @param isSource Specifies if the supplied variables are source-code or a path
 */
Shader::Shader(const std::string& vertex, const std::string& fragment, bool isSource) {
    if(!isSource){ //A path is provided
        try{
            readFileToBuffer(vertex, m_vertexShader);
        }catch(const std::ifstream::failure& e){
            std::cerr << "Could not read vertex file " << vertex << std::endl;
        }

        try{
            readFileToBuffer(fragment, m_fragmentShader);
        }catch(const std::ifstream::failure& e){
            std::cerr << "Could not read fragment file " << vertex << std::endl;
        }
    }else{
        m_vertexShader = vertex;
        m_fragmentShader = fragment;
    }

    m_programID = compileAndLink();
    cacheUniformLocations();
}

/**
 * @param vertex The vertex shader source or path depending on 'isSource'
 * @param fragment The fragment shader source or path depending on 'isSource'
 * @param geometry The geometry shader source or path depending on 'isSource'
 * @param isSource Specifies if the supplied variables are source-code or a path
 */
Shader::Shader(const std::string& vertex, const std::string& fragment, const std::string& geometry, bool isSource) {
    if(!isSource){ //A path is provided
        try{
            readFileToBuffer(vertex, m_vertexShader);
        }catch(const std::ifstream::failure& e){
            std::cerr << "Could not read vertex file " << vertex << std::endl;
        }

        try{
            readFileToBuffer(fragment, m_fragmentShader);
        }catch(const std::ifstream::failure& e){
            std::cerr << "Could not read fragment file " << vertex << std::endl;
        }

        try{
            readFileToBuffer(geometry, m_geometryShader);
        }catch(const std::ifstream::failure& e){
            std::cerr << "Could not read geometry file " << vertex << std::endl;
        }
    }else{
        m_vertexShader = vertex;
        m_fragmentShader = fragment;
        m_geometryShader = geometry;
    }

    m_programID = compileAndLink();
    cacheUniformLocations();
}


/**
 * @param type The type of shader to be compiled. eg. GL_FRAGMENT_SHADER
 * @param src The source code of the shader
 * @return The program-id of the given shader
 */
GLuint Shader::compileShader(GLenum type, const std::string& src) const {
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
GLuint Shader::linkShader(GLuint vertex, GLuint fragment, GLuint geometry) const {
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
GLuint Shader::compileAndLink() const {
    GLuint vertexShader   = (!m_vertexShader.empty())   ? compileShader(GL_VERTEX_SHADER,   m_vertexShader)   : 0;
    GLuint fragmentShader = (!m_fragmentShader.empty()) ? compileShader(GL_FRAGMENT_SHADER, m_fragmentShader) : 0;
    GLuint geometryShader = (!m_geometryShader.empty()) ? compileShader(GL_GEOMETRY_SHADER, m_geometryShader) : 0;

    return linkShader(vertexShader, fragmentShader, geometryShader);
}

/***
 * @brief Requests the uniform locations from the GPU for caching
 */
void Shader::cacheUniformLocations() {
    GLint amount;
    glGetProgramiv(m_programID, GL_ACTIVE_UNIFORMS, &amount);

    for (GLuint i = 0; i < amount; i++) {
        char* name = new char[16];
        GLsizei lenght;
        GLint size;
        GLenum type;
        glGetActiveUniform(m_programID, i, 16, &lenght, &size, &type, name);
        m_uniformLocations.insert(std::pair<std::string, GLuint>(std::string(name), i));
    }
}

/**
 * @brief Binds the shader if needed
 */
void Shader::bindProgram() const {
    if(lastBoundProgramID != m_programID){
        glUseProgram(m_programID);
        lastBoundProgramID = m_programID;
    }
}

GLuint Shader::getProgramID() const {
    return m_programID;
}


/***
 * @brief Sets the uniform of the current shader
 * @param uniform Uniform name. eg. "color"
 * @param value The value to set
 */
void Shader::setUniform(const std::string& uniform, GLint value) const {
    bindProgram();
    glUniform1i(m_uniformLocations.at(uniform), value);
}

/***
 * @brief Sets the uniform of the current shader
 * @param uniform Uniform name. eg. "color"
 * @param value The value to set
 */
void Shader::setUniform(const std::string& uniform, GLuint value) const {
    bindProgram();
    glUniform1ui(m_uniformLocations.at(uniform), value);
}

/***
 * @brief Sets the uniform of the current shader
 * @param uniform Uniform name. eg. "color"
 * @param value The value to set
 */
void Shader::setUniform(const std::string& uniform, GLfloat value) const {
    bindProgram();
    glUniform1f(m_uniformLocations.at(uniform), value);
}

/***
 * @brief Sets the uniform of the current shader
 * @param uniform Uniform name. eg. "color"
 * @param value The value to set
 */
void Shader::setUniform(const std::string& uniform, GLdouble value) const {
    bindProgram();
    glUniform1d(m_uniformLocations.at(uniform), value);
}

/***
 * @brief Sets the uniform of the current shader
 * @param uniform Uniform name. eg. "color"
 * @param value The value to set
 */
void Shader::setUniform(const std::string& uniform, const glm::vec2& value) const {
    bindProgram();
    glUniform2f(m_uniformLocations.at(uniform), value.x, value.y);
}

/***
 * @brief Sets the uniform of the current shader
 * @param uniform Uniform name. eg. "color"
 * @param value The value to set
 */
void Shader::setUniform(const std::string& uniform, const glm::vec3& value) const {
    bindProgram();
    glUniform3f(m_uniformLocations.at(uniform), value.x, value.y, value.z);
}

/***
 * @brief Sets the uniform of the current shader
 * @param uniform Uniform name. eg. "color"
 * @param value The value to set
 */
void Shader::setUniform(const std::string& uniform, const glm::vec4& value) const {
    bindProgram();
    glUniform4f(m_uniformLocations.at(uniform), value.r, value.g, value.b, value.a);
}

/***
 * @brief Sets the uniform of the current shader
 * @param uniform Uniform name. eg. "color"
 * @param value The value to set
 */
void Shader::setUniform(const std::string& uniform, const glm::mat4x4& value) const {
    bindProgram();
    glUniformMatrix4fv(m_uniformLocations.at(uniform), 1, GL_FALSE, &value[0][0]);
}



}

















