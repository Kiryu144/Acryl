#include "vertexbufferobject.h"

/***
 * @param data The pointer to the beginning of the data array
 * @param dataSize The complete size of the data array
 * @param type The type of data array passed. eg. GL_FLOAT
 * @param size The size per vertice. So for a 3D point it would be '3'; for uv '2'; and so on ..
 */
Acryl::VertexBufferObject::VertexBufferObject(void* data, GLint dataSize, GLint sizePerElement)
    : mSizeInMemory(dataSize), mSizePerElement(sizePerElement) {
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
}

Acryl::VertexBufferObject::~VertexBufferObject() {
    glDeleteBuffers(1, &mVBO);
}

unsigned int Acryl::VertexBufferObject::getVerticeAmount() const {
    return mSizeInMemory / (mSizePerElement * sizeof(float));
}

/***
 * @brief Binds the VBO to a vertex location for the shader
 * @param location The location to bind to
 */
void Acryl::VertexBufferObject::bindVertexAttribArray(GLuint location) const {
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glVertexAttribPointer(location, mSizePerElement, GL_FLOAT, GL_FALSE, 0, nullptr);
}
