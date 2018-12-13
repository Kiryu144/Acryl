#include "texture.h"

namespace Acryl {

Texture::Texture() {
    glGenTextures(1, &m_textureID);
}

/**
 * @brief Loads an image from disk and puts it into an opengl buffer
 * @param imagePath The image file path. Supported is *.png, *.jpg, *.jpeg, *.tif, *.webp
 */
Texture::Texture(const std::string& imagePath) {
    glGenTextures(1, &m_textureID);
    SDL_Surface* surface = IMG_Load(imagePath.c_str());
    if(surface == nullptr){
        throw std::logic_error("Could not parse file " + imagePath + "! Error: " + IMG_GetError());
    }

    int format = (surface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;

    uploadImageData(surface->pixels, surface->w, surface->h, format);
    SDL_FreeSurface(surface);
}

/**
 * @param imageData Starting point of the imagedata array
 * @param width Image width in pixels
 * @param heigth Image heigth in pixels
 * @param format Format of the data array. (GL_RGBA, GL_RGB, ...)
 */
Texture::Texture(void* imageData, unsigned int width, unsigned int heigth, GLenum format) {
    glGenTextures(1, &m_textureID);
    uploadImageData(imageData, width, heigth, format);
}

Texture::Texture(PixelField& pixelField)
    : Texture(pixelField.getData(), pixelField.getWidth(), pixelField.getHeight(), GL_RGBA) {
}

Texture::~Texture() {
    glDeleteTextures(1, &m_textureID);
}

/**
 * @param imageData Starting point of the imagedata array
 * @param width Image width in pixels
 * @param heigth Image heigth in pixels
 * @param format Format of the data array. (GL_RGBA, GL_RGB, ...)
 */
void Texture::uploadImageData(void* imageData, unsigned int width, unsigned int heigth, GLenum format) {
    bindTexture(0);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, heigth, 0, format, GL_UNSIGNED_BYTE, imageData);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    m_size.x = width;
    m_size.y = heigth;
}

/**
 * @brief Binds the texture and sets GL_TEXTURE<location> active
 * @param location The texture location (0-31)
 */
void Texture::bindTexture(GLuint location) const {
    glActiveTexture(GL_TEXTURE0 + location);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
}

GLuint Texture::getTextID() const {
    return m_textureID;
}

const glm::vec2& Texture::getSize() const {
    return m_size;
}




}