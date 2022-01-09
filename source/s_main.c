#include "window.h"
#include "shady.h"

#define CURRENT_FOLDER "examples/rtweekend_1/"

/* ---------- GLFW CALLBACKS -------- */
void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_F5 && action == GLFW_PRESS) {
        int loaded = shady_load(CURRENT_FOLDER"vertex.glsl", CURRENT_FOLDER"fragment.glsl");

        if (loaded == SHADY_OPENGL_FINE)
            printf("[Shady] : live-reload complete...\n");
        else
            printf("[Shady] : live-reload failed...\n");
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

/* ---------- Main -------- */
int main(int argc, char const *argv[]) {
    GLFWwindow* window = window_create(glfw_key_callback);

    shady_init();

    if (argc == 2) {
        #if defined(_WIN32)
            shady_load(argv[1]"vertex.glsl", argv[1]"fragment.glsl");
        #else
            shady_load_folder(argv[1]);
        #endif
    } else {
        printf("Expected usage: shady [arg1]\nWhere 'arg1' is the shader folder path.\n");
        exit(EXIT_FAILURE);
    }

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
