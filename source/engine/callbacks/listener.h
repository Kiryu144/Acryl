#ifndef ACRYL_LISTENER_H
#define ACRYL_LISTENER_H

#include <list>



namespace Acryl {
class Window;
class Listener;

class Listener {
private:
    static std::list<Listener*> m_handler;
public:
    Listener();
    Listener(const Listener& other);
    ~Listener();

    Listener& operator=(const Listener& other) = delete;

    //Calls
    static void fire_WindowResize(Window* window, int oldWidth, int oldHeight);

    //Listens
    virtual void onWindowResize(Window* window, int oldWidth, int oldHeight);
};

}

#endif //ACRYL_LISTENER_H
