#include "framebuffer.h"

Acryl::Framebuffer::Framebuffer(int width, int height)
    : m_texture(nullptr, width, height, GL_RGBA) {
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture.getTextID(), 0);
}

Acryl::Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &m_fbo);
}

void Acryl::Framebuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

void Acryl::Framebuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

const Acryl::Texture& Acryl::Framebuffer::getTexture() const {
    return m_texture;
}
