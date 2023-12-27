#pragma once

#include <iostream>
#include <queue>
#include <cstring>
#include <cassert>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"
#include "surface.hpp"
#include "ui.hpp"


namespace shady {

    typedef enum {
        LOAD_SHADERS,
        REFRESH_SHADERS,
        QUIT,
    } EventType;

    typedef struct Event {
        EventType type;
        std::string message;

        Event(EventType type, std::string message) {
            this->type = type;
            this->message = message;
        }
    } Event;

    static std::queue<Event> EventQueue;

    class Shady {
    public:
        Surface surface;

        Shady(int width, int height);
        ~Shady();

        void run();
    private:
        int width;
        int height;
        GLFWwindow *pWindow;

        void handle_uniforms();
        void topbar_menu();
    };

}
