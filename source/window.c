#include "window.h"

GLFWwindow* window_create(GLFWkeyfun key_callback) {
    if (!glfwInit()) {
        return NULL;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);


    /* glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); */
    GLFWwindow* window = glfwCreateWindow(640, 480, "shady", NULL, NULL);
    if (!window) {
        printf("aaaaaaaaaaaaaa");
        return NULL;
    }

    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    if (GLAD_GL_VERSION_3_3) {
        printf("aaaaaaa\n");
    }

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
