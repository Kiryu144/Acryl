#include "window.h"

namespace Acryl {

Window::Window(const std::string& title, unsigned int width, unsigned int heigth)
    : mWindowTitle(title), mWidth(width), mHeigth(heigth), mSdlWindow(nullptr) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    mSdlWindow = SDL_CreateWindow(mWindowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mWidth, mHeigth, SDL_WINDOW_OPENGL);

    //Create context and bind it
    mContext = SDL_GL_CreateContext(mSdlWindow); //Create new context for window

    //Some OpenGL related settings
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND );
    //
}

Window::~Window() {
    SDL_DestroyWindow(mSdlWindow);
}

void Window::hide() {
    SDL_HideWindow(mSdlWindow);
}

void Window::show() {
    SDL_ShowWindow(mSdlWindow);
}

const std::string& Window::getWindowTitle() const {
    return mWindowTitle;
}

unsigned int Window::getWidth() const {
    return mWidth;
}

unsigned int Window::getHeigth() const {
    return mHeigth;
}

}