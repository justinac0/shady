#pragma once

#include <iostream>
#include <cstring>
#include <cassert>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"
#include "surface.hpp"


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
    };

}
