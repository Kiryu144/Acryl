#include "transformation.h"

namespace Acryl {

Transformation::Transformation() = default;

Transformation::Transformation(const glm::vec3& position)
    : m_position(position) {
    calculateModelMatrix();
}

Transformation::Transformation(const glm::vec3& position, const glm::vec3& rotation)
    : m_position(position), m_rotation(rotation) {
    calculateModelMatrix();
}

Transformation::Transformation(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
    : m_position(position), m_rotation(rotation), m_scale(scale) {
    calculateModelMatrix();
}

/**
 * @brief Recalculates the model matrix for the store position, rotation and scale
 */
void Transformation::calculateModelMatrix() {
    m_matrix = glm::mat4(1.0f);
    m_matrix = glm::translate(m_matrix, m_position);
    m_matrix = glm::rotate(   m_matrix, m_rotation.x, glm::vec3(1, 0, 0));
    m_matrix = glm::rotate(   m_matrix, m_rotation.y, glm::vec3(0, 1, 0));
    m_matrix = glm::rotate(   m_matrix, m_rotation.z, glm::vec3(0, 0, 1));
    m_matrix = glm::scale(    m_matrix, m_scale);
}

const glm::vec3& Transformation::getPosition() const {
    return m_position;
}

void Transformation::setPosition(const glm::vec3& position) {
    if(m_position != position){
        m_position = position;
        calculateModelMatrix();
    }
}

const glm::vec3& Transformation::getRotation() const {
    return m_rotation;
}

void Transformation::setRotation(const glm::vec3& rotation) {
    if(m_rotation != rotation){
        m_rotation = rotation;
        calculateModelMatrix();
    }
}

const glm::vec3& Transformation::getScale() const {
    return m_scale;
}

void Transformation::setScale(const glm::vec3& scale) {
    if(m_scale != scale){
        m_scale = scale;
        calculateModelMatrix();
    }
}

const glm::mat4& Transformation::getMatrix() const {
    return m_matrix;
}

}