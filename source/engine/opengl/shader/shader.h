#ifndef ACRYL_GLSHADERCOMPILER_H
#define ACRYL_GLSHADERCOMPILER_H

#include <string>
#include <iostream>
#include <map>
#include <GLEW/glew.h>
#include <GLM/common.hpp>
#include <GLM/vec2.hpp>
#include <array>
#include <GLM/vec3.hpp>
#include <GLM/vec4.hpp>
#include <GLM/mat4x4.hpp>

#include "../../util/util.h"

namespace Acryl {

class Shader {
private:
    static GLuint lastBoundProgramID;

    std::string m_vertexShader;
    std::string m_fragmentShader;
    std::string m_geometryShader;
    GLuint m_programID;

    std::map<std::string, GLuint> m_uniformLocations;

    GLuint compileAndLink() const;
    GLuint compileShader(GLenum type, const std::string& src) const;
    GLuint linkShader(GLuint vertex, GLuint fragment, GLuint geometry = 0) const;
    void cacheUniformLocations();
    GLuint getUniformLocation(const std::string& s) const;
public:
    Shader(const std::string& vertex, const std::string& fragment, bool isSource = false);
    Shader(const std::string& vertex, const std::string& fragment, const std::string& geometry, bool isSource);

    Shader(const Shader& other) = delete; //Removes copy constructor
    void operator=(const Shader& other) = delete; //Removes assingment operator

    void bindProgram() const;
    GLuint getProgramID() const;

    void setUniform(const std::string& uniform, GLint value) const;
    void setUniform(const std::string& uniform, GLuint value) const;
    void setUniform(const std::string& uniform, GLuint* values, size_t amount) const;
    void setUniform(const std::string& uniform, GLfloat value) const;
    void setUniform(const std::string& uniform, GLdouble value) const;

    void setUniform(const std::string& uniform, const glm::vec2& value) const;
    void setUniform(const std::string& uniform, const glm::vec3& value) const;
    void setUniform(const std::string& uniform, const glm::vec4& value) const;
    void setUniform(const std::string& uniform, const glm::mat4x4& value) const;
};

}

#endif
