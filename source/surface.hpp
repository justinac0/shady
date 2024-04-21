#pragma once

#include <iostream>
#include <string>
#include <glad/glad.h>

#include "shader.hpp"

namespace shady {

    class Surface {
    public:
        Surface();
        ~Surface();

        void begin_draw();
        void end_draw();

        GLuint get_program_id();

        static GLuint create_quad(int x, int y, float w, float h);
        static Surface load_shader_dir_surface(std::string path);
        static Surface load_shader_surface(std::string vertex_shader, std::string fragment_shader);

    // private:
        GLuint vertex;
        GLuint fragment;
        GLuint program;
        GLuint surface;
    };

}
