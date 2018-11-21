#ifndef ACRYL_WINDOW_H
#define ACRYL_WINDOW_H

#include <string>
#include <SDL2/SDL.h>
#include <GLEW/glew.h>
#include <iostream>

namespace Acryl{

class Window {
private:
    std::string mWindowTitle;
    unsigned int mWidth, mHeigth;

    SDL_Window* mSdlWindow;
    SDL_GLContext mContext;
public:
    Window(const std::string& title, unsigned int width = 900, unsigned int heigth = 600);
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
