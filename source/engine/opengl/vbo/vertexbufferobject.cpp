#include "vertexbufferobject.h"

/***
 * @param data The pointer to the beginning of the data array
 * @param dataSize The complete size of the data array
 * @param type The type of data array passed. eg. GL_FLOAT
 */
Acryl::VertexBufferObject::VertexBufferObject(void* data, GLint dataSize, GLenum type)
    : mSizeInMemory(dataSize),  mType(type) {
    glGenBuffers(1, &mVBO);
    glBindBuffer(1, mVBO);
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
}

Acryl::VertexBufferObject::~VertexBufferObject() {
    glDeleteBuffers(1, &mVBO);
}

/***
 * @brief Binds the VBO to a vertex location for the shader
 * @param location The location to bind to
 */
void Acryl::VertexBufferObject::bindVertexAttribArray(GLuint location) {
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glVertexAttribPointer(location, mSizeInMemory, mType, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(location);
}
