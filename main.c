#include "shady.h"

#include <glad.h>
#include <GLFW/glfw3.h>

char* read_file(const char* file_path) {
    FILE* file_stream = fopen(file_path, "r");
	if (!file_stream) return NULL;

    fseek(file_stream, 0, SEEK_END);
    size_t length = ftell(file_stream);
    rewind(file_stream);
    char* buffer = (char*)calloc(length, sizeof(char));
    if (!buffer) return NULL;

    fread(buffer, sizeof(char), length, file_stream);

    fclose(file_stream);

    return buffer;
}

s_Program program;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_F5 && action == GLFW_PRESS) {
        glDeleteProgram(program);
        
        const char* vertex_source = read_file("shaders/default/vertex.glsl");
        printf("%s\n", vertex_source);
        s_Shader vertex_shader = s_create_shader(vertex_source, GL_VERTEX_SHADER);
        free(vertex_source);

        const char* fragment_source = read_file("shaders/default/fragment.glsl");
        printf("%s\n", fragment_source);
        s_Shader fragment_shader = s_create_shader(fragment_source, GL_FRAGMENT_SHADER);
        free(fragment_source);

        program = s_create_program(vertex_shader, fragment_shader);
    }
}

int main(int argc, char const *argv[]) {
    if (!glfwInit()) {
        return NULL;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "shady", NULL, NULL);
    if (!window) {
        return NULL;
    }

    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    glfwSwapInterval(1);

    const char* vertex_source = read_file("shaders/default/vertex.glsl");
    printf("%s\n", vertex_source);
    s_Shader vertex_shader = s_create_shader(vertex_source, GL_VERTEX_SHADER);
    free(vertex_source);

    const char* fragment_source = read_file("shaders/default/fragment.glsl");
    printf("%s\n", fragment_source);
    s_Shader fragment_shader = s_create_shader(fragment_source, GL_FRAGMENT_SHADER);
    free(fragment_source);

    program = s_create_program(vertex_shader, fragment_shader);

    uint32_t surface = s_create_surface();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0, 0, 0, 1);

        int width, height;
        glfwGetWindowSize(window, &width, &height);
        glViewport(0, 0, width, height);

        GLuint res[2] = { width, height };
        glUniform1f(glGetUniformLocation(program, "u_ScreenResolution_x"), width);
        glUniform1f(glGetUniformLocation(program, "u_ScreenResolution_y"), height);

        double mouse_x, mouse_y;
        glfwGetCursorPos(window, &mouse_x, &mouse_y);
        glUniform1f(glGetUniformLocation(program, "u_Mouse_x"), mouse_x);
        glUniform1f(glGetUniformLocation(program, "u_Mouse_y"), mouse_y);

        glUniform1f(glGetUniformLocation(program, "u_Time"), glfwGetTime());

        glUseProgram(program);
        s_update_surface(surface, program);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}
