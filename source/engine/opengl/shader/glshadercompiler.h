#ifndef ACRYL_GLSHADERCOMPILER_H
#define ACRYL_GLSHADERCOMPILER_H

#include <string>
#include <iostream>
#include <GLEW/glew.h>

#include "../../util/util.h"

namespace Acryl {

class GLShaderCompiler {
private:
    std::string mVertexShader;
    std::string mFragmentShader;
    std::string mGeometryShader;

    GLuint compileShader(GLenum type, const std::string& src) const;
    GLuint linkShader(GLuint vertex, GLuint fragment, GLuint geometry = 0) const;
public:
    GLShaderCompiler(const std::string& vertex, const std::string& fragment, bool isSource = false);
    GLShaderCompiler(const std::string& vertex, const std::string& fragment, const std::string& geometry, bool isSource);

    GLuint compileAndLink() const;
};

}

#endif
