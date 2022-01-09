#include "window.h"

GLFWwindow* window_create(GLFWkeyfun key_callback) {
    if (!glfwInit()) {
        return NULL;
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(1280, 720, "shady", NULL, NULL);
    if (!window) {
        return NULL;
    }

    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    glfwSwapInterval(1);

    return window;
}

void window_destroy(GLFWwindow* window) {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void window_update(GLFWwindow* window) {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool window_should_close(GLFWwindow* window) {
    return glfwWindowShouldClose(window);
}
