#ifndef ACRYL_VERTEXBUFFEROBJECT_H
#define ACRYL_VERTEXBUFFEROBJECT_H

#include <cstdio>
#include <GLEW/glew.h>

namespace Acryl {

class VertexBufferObject {
private:
    GLint mSizeInMemory;
    GLuint mVBO;
    GLint mSizePerElement;
public:
    VertexBufferObject(void* data, GLint dataSize, GLint sizePerElement);
    ~VertexBufferObject();

    VertexBufferObject(const VertexBufferObject& other) = delete;
    VertexBufferObject& operator=(const VertexBufferObject& other) = delete;

    void bindVertexAttribArray(GLuint location) const;
    unsigned int getVerticeAmount() const;
};

}

#endif
