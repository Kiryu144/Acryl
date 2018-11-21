#ifndef ACRYL_TEXTURE_H
#define ACRYL_TEXTURE_H

#include <GLEW/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GLM/vec2.hpp>
#include <GLM/vec4.hpp>
#include <string>
#include <stdexcept>

namespace Acryl {

class Texture {
private:
    GLuint mTextID;
    glm::vec2 size;

    void uploadImageData(void* imageData, unsigned int width, unsigned int heigth, GLenum format);
public:
    Texture();
    Texture(const std::string& imagePath);
    Texture(void* imageData, unsigned int width, unsigned int heigth, GLenum format);
    ~Texture();

    Texture(const Texture& texture) = delete; //TODO: Implement deep copy

    void bindTexture(GLuint location) const;

    GLuint getTextID() const;
    const glm::vec2& getSize() const;
};

}

#endif
