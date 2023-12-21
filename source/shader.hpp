#pragma once

#include <iostream>
#include <cstring>

#include <glad/glad.h>

namespace shady {

    class Shader {
    public:
        static GLuint create_program(GLuint vertex, GLuint fragment);
        static GLuint load(std::string file_path, GLenum type);
    };

}