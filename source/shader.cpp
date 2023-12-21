#include "shader.hpp"


char* read_file(const char* path) {
    FILE* fileStream = fopen(path, "r");
    if (!fileStream) {
        printf("could not find file: %s\n", path);
        return NULL;
    }

    fseek(fileStream, SEEK_SET, SEEK_END);
    size_t length = ftell(fileStream);
    rewind(fileStream);
    char* buffer = (char*) calloc(length + 1, sizeof(char));
    fread(buffer, sizeof(char), length, fileStream);
    return buffer;
}


GLuint shady::Shader::create_program(GLuint vertex, GLuint fragment) {
    GLuint program = glCreateProgram();

    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    
    glLinkProgram(program);

    GLint linked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int*)&linked);

    if (linked == 0) {
        GLint length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

        GLchar* log = (GLchar*) calloc(length + 1, sizeof(GLchar));
        glGetProgramInfoLog(program, length, &length, &log[0]);

        printf("[shader_program] -- %s\n", log);
        free(log);

        glDeleteProgram(program);
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    glDetachShader(program, vertex);
    glDetachShader(program, fragment);

    return program;
}


GLuint shady::Shader::load(std::string file_path, GLenum type) {
    GLuint id = glCreateShader(type);

    const char* source = read_file(file_path.c_str());
    const GLint length = strlen(source);

    glShaderSource(id, 1, (const char* const*)&source, &length);
    glCompileShader(id);

    GLint success = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if (success == 0) {
        GLint length = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        GLchar* log = (GLchar*)calloc(length + 1, sizeof(GLchar));
        glGetShaderInfoLog(id, length, &length, &log[0]);

        std::cout << "[shader::" "]" << file_path.c_str() << " -- " << log << std::endl;
        free(log);

        glDeleteShader(id);
    }

    return id;
}