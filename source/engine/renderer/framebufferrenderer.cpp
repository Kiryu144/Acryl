#include "framebufferrenderer.h"

namespace Acryl {

FramebufferRenderer::FramebufferRenderer() {
    Acryl::Defaults::init();
    for (auto& i : m_framebuffer) {
        i = nullptr;
    }
}

void FramebufferRenderer::setFramebuffer(int i, Acryl::Framebuffer* buf) {
    m_framebuffer[i] = buf;
}

void FramebufferRenderer::render() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    Acryl::Defaults::Framebuffer->bindProgram();
    Acryl::Defaults::Plane_2D_X2->bindVertexAttribArray(0);
    Acryl::Defaults::Plane_2D_UV->bindVertexAttribArray(1);

    std::array<GLuint, 16> textureArray = {};

    int i = 0;
    for(Framebuffer* buffer : m_framebuffer){
        if(!buffer){
            continue;
        }

        buffer->getTexture().bindTexture(i);
        textureArray[i] = buffer->getTexture().getTextID();
        ++i;
    }

    Acryl::Defaults::Framebuffer->setUniform("sampler", &textureArray.at(0), i);

    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, i);
}

}