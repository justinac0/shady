#include "shady.hpp"


/* ------ SHADY -----------*/
void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}


shady::Shady::Shady(int width, int height) {
    this->width = width;
    this->height = height;

    if (!glfwInit()) {
        // assert
    }

    this->pWindow = glfwCreateWindow(this->width, this->height, "shady", nullptr, nullptr);
    if (!this->pWindow) assert(this->pWindow != NULL);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwSetKeyCallback(this->pWindow, glfw_key_callback);

    glfwMakeContextCurrent(this->pWindow);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
}


shady::Shady::~Shady() {
    glfwTerminate();
}


inline void shady::Shady::handle_uniforms() {
    const GLuint programID = this->surface.get_program_id();

    int width, height;
    glfwGetWindowSize(this->pWindow, &width, &height);

    GLfloat dimensions[2] = {(GLfloat)width, (GLfloat)height};
    glUniform2fv(glGetUniformLocation(programID, "uResolution"), 1, dimensions);

    glUniform1f(glGetUniformLocation(programID, "uTime"), glfwGetTime());

    double xpos, ypos;
    glfwGetCursorPos(this->pWindow, &xpos, &ypos);

    GLfloat mousePosition[2] = {(GLfloat)xpos, (GLfloat)ypos};
    glUniform2fv(glGetUniformLocation(programID, "uMouse"), 1, mousePosition);
}


void shady::Shady::run() {
    while (!glfwWindowShouldClose(pWindow)) {
        glfwPollEvents();

        this->surface.begin_draw();
        handle_uniforms();
        this->surface.end_draw();

        glfwSwapBuffers(this->pWindow);
    }
}