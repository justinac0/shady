#include "window.h"
#include "shady.h"

const char* CURRENT_FOLDER = "examples/rtweekend_1/";

void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_F5 && action == GLFW_PRESS) {
        int loaded = shady_load_folder(CURRENT_FOLDER);

        if (loaded == SHADY_OPENGL_FINE)
            printf("[Shady] : live-reload complete...\n");
        else
            printf("[Shady] : live-reload failed...\n");
    }
}

int main(int argc, char const *argv[]) {
    GLFWwindow* window = window_create(glfw_key_callback);

    shady_init();

    shady_load_folder(CURRENT_FOLDER);

    while (!window_should_close(window)) {
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        glViewport(0, 0, width, height);

        double mx, my;
        glfwGetCursorPos(window, &mx, &my);

        shady_send_vec2f(width, height, "u_ScreenResolution");
        shady_send_vec2f(mx, my, "u_Mouse");
        shady_send_float(glfwGetTime(), "u_Time");

        shady_update();

        window_update(window);
    }

    shady_terminate();
    window_destroy(window);

    return EXIT_SUCCESS;
}
