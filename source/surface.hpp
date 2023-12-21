#pragma once

#include <glad/glad.h>

#include "shader.hpp"

namespace shady {

    class Surface {
    public:
        Surface();
        ~Surface();

        void load(std::string vertexPath, std::string fragmentPath);
        void begin_draw();
        void end_draw();

        GLuint get_program_id();

    private:
        GLuint vertex;
        GLuint fragment;
        GLuint program;
        GLuint surface;
    };

}
