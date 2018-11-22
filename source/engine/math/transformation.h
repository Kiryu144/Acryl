#ifndef ACRYL_TRANSFORMATION_H
#define ACRYL_TRANSFORMATION_H


#define GLM_ENABLE_EXPERIMENTAL
#include <GLM/vec2.hpp>
#include <GLM/vec3.hpp>
#include <GLM/vec4.hpp>
#include <GLM/mat4x4.hpp>
#include <GLM/gtx/transform.hpp>

namespace Acryl {

class Transformation {
private:
    glm::vec3 mPosition;
    glm::vec3 mRotation;
    glm::vec3 mScale;

    glm::mat4 mMatrix;

    void calculateModelMatrix();
public:
    Transformation();
    Transformation(const glm::vec3& position);
    Transformation(const glm::vec3& position, const glm::vec3& rotation);
    Transformation(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);

    const glm::vec3& getPosition() const;
    void setPosition(const glm::vec3& position);

    const glm::vec3& getRotation() const;
    void setRotation(const glm::vec3& rotation);

    const glm::vec3& getScale() const;
    void setScale(const glm::vec3& scale);

    const glm::mat4& getMatrix() const;
};

}

#endif
