#include <engine/acryl.h>

int main(int argc, char** argv) {
    Acryl::Window window("Acryl");

    Acryl::Defaults::init();

    Acryl::Camera camera(Acryl::CameraType::ORTHOGRAPHIC, 0.0, 100.0, 40, Acryl::Transformation(glm::vec3(), glm::vec3(-180, 90, 0), glm::vec3()), window);
    camera.updateMatrices();

    Acryl::Texture atlas("./atlas.png");
    Acryl::TilemapRenderer tilemapRenderer(&atlas, nullptr, 64, 64);

    while(!window.quitRequested()){
        window.swap();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        tilemapRenderer.render(5, 5, 0);
        tilemapRenderer.render(5, 1, 0);
        tilemapRenderer.render(2, 3, 0);
        tilemapRenderer.render(5, 4, 0);
        tilemapRenderer.finalize(camera);
    }

    return 0;
}





/*
 *
 * int main(int argc, char** argv) {
    Acryl::Window window("Acryl");

    Acryl::Defaults::init();

    Acryl::Camera camera(Acryl::CameraType::ORTHOGRAPHIC, 0.0, 100.0, 40, Acryl::Transformation(glm::vec3(), glm::vec3(-180, 90, 0), glm::vec3()), window);
    camera.updateMatrices();

    Acryl::Texture atlas("./atlas.png");
    Acryl::TilemapRenderer tilemapRenderer(&atlas, nullptr, 64, 64);

    Acryl::Framebuffer framebuf(900, 600);
    framebuf.unbind();

    Acryl::Framebuffer framebuf2(900, 600);
    framebuf2.unbind();

    Acryl::FramebufferRenderer framebufferRenderer;
    framebufferRenderer.setFramebuffer(1, &framebuf);
    framebufferRenderer.setFramebuffer(0, &framebuf2);

    while(!window.quitRequested()){
        window.swap();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        framebuf.bind();
        tilemapRenderer.render(5, 5, 0);
        tilemapRenderer.render(5, 6, 0);
        tilemapRenderer.render(6, 6, 0);
        tilemapRenderer.finalize();
        framebuf.unbind();

        framebuf2.bind();
        tilemapRenderer.render(2, 2, 0);
        tilemapRenderer.render(3, 2, 0);
        tilemapRenderer.render(2, 3, 0);
        tilemapRenderer.finalize();
        framebuf2.unbind();

        framebufferRenderer.render();

    }

    return 0;
}
 * */