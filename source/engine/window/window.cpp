#include "window.h"

namespace Acryl {

/***
 * @param title The window title
 * @param width The window width in pixels
 * @param height The window heigth in pixels
 */
Window::Window(const std::string& title, unsigned int width, unsigned int height)
    : m_windowTitle(title), m_width(width), m_height(height), m_sdlWindow(nullptr) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    m_sdlWindow = SDL_CreateWindow(m_windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    //Create context and bind it
    m_context = SDL_GL_CreateContext(m_sdlWindow); //Create new context for window

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
    SDL_DestroyWindow(m_sdlWindow);
}

/***
 * @brief Hides the window, still visible in the task-manager of course
 */
void Window::hide() {
    SDL_HideWindow(m_sdlWindow);
}

/***
 * @brief Shows the window back if it has been hidden before
 */
void Window::show() {
    SDL_ShowWindow(m_sdlWindow);
}

const std::string& Window::getWindowTitle() const {
    return m_windowTitle;
}

unsigned int Window::getWidth() const {
    return m_width;
}

unsigned int Window::getHeigth() const {
    return m_height;
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
    SDL_GL_SwapWindow(m_sdlWindow);
}

}