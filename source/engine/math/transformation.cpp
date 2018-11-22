#include "transformation.h"

namespace Acryl {

Transformation::Transformation() = default;

Transformation::Transformation(const glm::vec3& position)
    : mPosition(position) {
    calculateModelMatrix();
}

Transformation::Transformation(const glm::vec3& position, const glm::vec3& rotation)
    : mPosition(position), mRotation(rotation) {
    calculateModelMatrix();
}

Transformation::Transformation(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
    : mPosition(position), mRotation(rotation), mScale(scale) {
    calculateModelMatrix();
}

/**
 * @brief Recalculates the model matrix for the store position, rotation and scale
 */
void Transformation::calculateModelMatrix() {
    mMatrix = glm::mat4(1.0f);
    mMatrix = glm::translate(mMatrix, mPosition);
    mMatrix = glm::rotate(   mMatrix, mRotation.x, glm::vec3(1, 0, 0));
    mMatrix = glm::rotate(   mMatrix, mRotation.y, glm::vec3(0, 1, 0));
    mMatrix = glm::rotate(   mMatrix, mRotation.z, glm::vec3(0, 0, 1));
    mMatrix = glm::scale(    mMatrix, mScale);
}

const glm::vec3& Transformation::getPosition() const {
    return mPosition;
}

void Transformation::setPosition(const glm::vec3& position) {
    if(mPosition != position){
        mPosition = position;
        calculateModelMatrix();
    }
}

const glm::vec3& Transformation::getRotation() const {
    return mRotation;
}

void Transformation::setRotation(const glm::vec3& rotation) {
    if(mRotation != rotation){
        mRotation = rotation;
        calculateModelMatrix();
    }
}

const glm::vec3& Transformation::getScale() const {
    return mScale;
}

void Transformation::setScale(const glm::vec3& scale) {
    if(mScale != scale){
        mScale = scale;
        calculateModelMatrix();
    }
}

const glm::mat4& Transformation::getMatrix() const {
    return mMatrix;
}

}