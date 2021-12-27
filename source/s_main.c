#include "window.h"
#include "shady.h"

const char* VERTEX_SHADER_PATH      = "examples/fractal/vertex.glsl";
const char* FRAGMENT_SHADER_PATH    = "examples/fractal/fragment.glsl";

void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_F5 && action == GLFW_PRESS) {
        shady_load(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
    }
}

int main(int argc, char const *argv[]) {
    GLFWwindow* window = window_create(glfw_key_callback);

    shady_init();
    shady_load(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);

    while (!window_should_close(window)) {

        int width, height;
        glfwGetWindowSize(window, &width, &height);
        glViewport(0, 0, width, height);

        double mx, my;
        glfwGetCursorPos(window, &mx, &my);

        shady_send_uniforms(width, height, mx, my, glfwGetTime());
        shady_update();

        window_update(window);
    }

    shady_terminate();
    window_destroy(window);

    return EXIT_SUCCESS;
}
