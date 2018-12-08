#include "vertexbufferobject.h"

/***
 * @param data The pointer to the beginning of the data array
 * @param dataSize The complete size of the data array
 * @param type The type of data array passed. eg. GL_FLOAT
 * @param size The size per vertice. So for a 3D point it would be '3'; for uv '2'; and so on ..
 */
Acryl::VertexBufferObject::VertexBufferObject(void* data, GLint dataSize, GLint sizePerElement)
    : m_sizeInMemory(dataSize), m_sizePerElement(sizePerElement) {
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
}

Acryl::VertexBufferObject::~VertexBufferObject() {
    glDeleteBuffers(1, &m_vbo);
}

/***
 * @brief Calculates the amount of vertices present in the VBO
 * @return The number of vertices present
 */
unsigned int Acryl::VertexBufferObject::getVerticeAmount() const {
    return m_sizeInMemory / (m_sizePerElement * sizeof(float));
}

/***
 * @brief Binds the VBO to a vertex location for the shader
 * @param location The location to bind to
 */
void Acryl::VertexBufferObject::bindVertexAttribArray(GLuint location) const {
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glVertexAttribPointer(location, m_sizePerElement, GL_FLOAT, GL_FALSE, 0, nullptr);
}
