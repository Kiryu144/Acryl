#include "tilemaprenderer.h"

namespace Acryl {

TilemapRenderer::TilemapRenderer(Texture* atlas, Texture* dest, int elementsPerRow, int tileSize)
    : m_textureAtlas(atlas), m_destinationTexture(dest), m_elementsPerRow(elementsPerRow), m_pixelPerElement(atlas->getSize().x/elementsPerRow) {
    Acryl::Defaults::init();
    Transformation transformation = Transformation(glm::vec3(0), glm::vec3(0), glm::vec3(tileSize));
    m_modelMatrix = transformation.getMatrix();
}

void TilemapRenderer::render(float x, float y, int index) {
    m_renderData.push_back(glm::vec3(x, y, index));
}

void TilemapRenderer::finalize(const Camera& camera) {
    if(m_renderData.empty()){
        return;
    }

    m_instancedRenderBuffer = std::unique_ptr<VertexBufferObject>(new VertexBufferObject(&m_renderData.at(0), m_renderData.size() * sizeof(float) * 3, 3));


    Acryl::Defaults::iTexture2D->bindProgram();
    m_textureAtlas->bindTexture(0);

    Acryl::Defaults::iTexture2D->setUniform("rowCount", float(m_elementsPerRow));
    Acryl::Defaults::iTexture2D->setUniform("mvp", camera.getProjection() * camera.getView() * m_modelMatrix);

    Acryl::Defaults::Plane_2D->bindVertexAttribArray(0);
    Acryl::Defaults::Plane_2D_UV->bindVertexAttribArray(1);
    m_instancedRenderBuffer->bindVertexAttribArray(2, true);

    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, m_renderData.size());
    m_renderData.clear();
}


}