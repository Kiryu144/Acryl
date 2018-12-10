#ifndef ACRYL_FRAMEBUFFERRENDERER_H
#define ACRYL_FRAMEBUFFERRENDERER_H

#include "../opengl/framebuffer/framebuffer.h"
#include "../defaults.h"
#include <array>

namespace Acryl {

class FramebufferRenderer {
private:
    std::array<Framebuffer*, 16> m_framebuffer;
public:
    FramebufferRenderer();

    void setFramebuffer(int i, Framebuffer* buf);
    void render();
};

}

#endif
