#pragma once

#include <iostream>
#include <queue>
#include <cstring>
#include <cassert>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "debug.hpp"
#include "shader.hpp"
#include "surface.hpp"
#include "ui.hpp"

namespace shady {

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
