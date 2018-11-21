#ifndef ACRYL_VERTEXBUFFEROBJECT_H
#define ACRYL_VERTEXBUFFEROBJECT_H

#include <cstdio>
#include <GLEW/glew.h>

namespace Acryl {

class VertexBufferObject {
private:
    GLint mSizeInMemory;
    GLuint mVBO;
public:
    VertexBufferObject(void* data, GLint dataSize);
    ~VertexBufferObject();

    void bindVertexAttribArray(GLuint location);
};

}

#endif
