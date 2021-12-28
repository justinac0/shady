#include "window.h"

GLFWwindow* window_create(GLFWkeyfun key_callback) {
    if (!glfwInit()) {
        return NULL;
    }

    /* glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); */
    GLFWwindow* window = glfwCreateWindow(640, 480, "shady", NULL, NULL);
    if (!window) {
        return NULL;
    }

    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    glfwSwapInterval(1);

    glViewport(0, 0, 640, 480);

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
