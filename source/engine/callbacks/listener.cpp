#include "listener.h"

namespace Acryl {

void fire_WindowResize(Window* window, int oldWidth, int oldHeight);

std::list<Listener*> Listener::m_handler;

Listener::Listener() {
    m_handler.push_back(this);
}

Listener::Listener(const Listener& other) {
    m_handler.push_back(this);
}

Listener::~Listener() {
    m_handler.remove(this);
}

void Listener::fire_WindowResize(Window* window, int oldWidth, int oldHeight) {
    for(Listener* listener : m_handler){
        listener->onWindowResize(window, oldWidth, oldHeight);
    }
}

void Listener::onWindowResize(Window* window, int oldWidth, int oldHeight) { }

}