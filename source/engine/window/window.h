#ifndef ACRYL_WINDOW_H
#define ACRYL_WINDOW_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GLEW/glew.h>
#include <iostream>

namespace Acryl{

class Window {
private:
    std::string m_windowTitle;
    unsigned int m_width, m_height;

    SDL_Window* m_sdlWindow;
    SDL_GLContext m_context;
public:
    Window(const std::string& title, unsigned int width = 900, unsigned int height = 600);
    ~Window();

    void hide();
    void show();

    const std::string& getWindowTitle() const;
    unsigned int getWidth() const;
    unsigned int getHeigth() const;
    bool quitRequested() const;
    void swap() const;
};

}

#endif
