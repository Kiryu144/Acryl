#ifndef ACRYL_FRAMEBUFFER_H
#define ACRYL_FRAMEBUFFER_H

#include "../texture/texture.h"

namespace Acryl{

class Framebuffer {
private:
    GLuint m_fbo;
    Texture m_texture;
public:
    Framebuffer(int width, int height);
    ~Framebuffer();

    void operator=(const Framebuffer& other) = delete;
    Framebuffer(const Framebuffer& other) = delete;

    void bind();
    void unbind();

    const Texture& getTexture() const;
};

}

#endif
