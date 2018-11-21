#include "window.h"

namespace Acryl {

/***
 * @param title The window title
 * @param width The window width in pixels
 * @param heigth The window heigth in pixels
 */
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

    //Load SDL_Image
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);

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

/***
 * @brief Hides the window, still visible in the task-manager of course
 */
void Window::hide() {
    SDL_HideWindow(mSdlWindow);
}

/***
 * @brief Shows the window back if it has been hidden before
 */
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

/***
 * @return True if quitting is requested by the OS or the user
 */
bool Window::quitRequested() const {
    return SDL_QuitRequested();
}

/***
 * @brief Swaps the current drawing buffer
 */
void Window::swap() const {
    SDL_GL_SwapWindow(mSdlWindow);
}

}