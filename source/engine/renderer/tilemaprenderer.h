#ifndef ACRYL_TILEMAPRENDERER_H
#define ACRYL_TILEMAPRENDERER_H

#include "../opengl/texture/texture.h"
#include "../opengl/vbo/vertexbufferobject.h"
#include <vector>
#include <GLM/vec3.hpp>
#include "../defaults.h"
#include "../math/transformation.h"
#include "../math/camera.h"

namespace Acryl {

class TilemapRenderer {
private:
    Texture* m_textureAtlas;
    Texture* m_destinationTexture;

    glm::mat4 m_modelMatrix;

    int m_elementsPerRow;
    int m_pixelPerElement;

    std::unique_ptr<VertexBufferObject> m_instancedRenderBuffer;
    std::vector<glm::vec3> m_renderData; //(x, y, i)
public:
    TilemapRenderer(Texture* atlas, Texture* dest, int elementsPerRow, int tileSize);

    void render(float x, float y, int index);
    void finalize(const Camera& camera);
};

}

#endif
