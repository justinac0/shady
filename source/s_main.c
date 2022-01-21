#include "window.h"
#include "shady.h"

#define CURRENT_FOLDER "examples/rtweekend_1/"

/* FIXME: move these globals into the shady state */
bool isPaused = false;
double realTime = 0;
double currentDelta = 0;

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

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        isPaused = !isPaused;
    }

    if (isPaused) {
        if (key == GLFW_KEY_A && action == GLFW_REPEAT) {
            realTime += currentDelta;
        }

        if (key == GLFW_KEY_D && action == GLFW_REPEAT) {
            realTime -= currentDelta;
        }
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


    double lastTime = glfwGetTime();
    while (!window_should_close(window)) {
        double currentTime = glfwGetTime();
        currentDelta = currentTime - lastTime;

        int width, height;
        double mx, my;

        glfwGetWindowSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glfwGetCursorPos(window, &mx, &my);
        shady_send_vec2f(width, height, "u_ScreenResolution");
        shady_send_vec2f(mx, my, "u_Mouse");

        shady_send_float(realTime, "u_Time");

        if (!isPaused) {
            realTime += currentDelta;
        }

        if (currentTime - lastTime > 1.0/120.0) {
            lastTime = currentTime;
        }

        shady_update();

        window_update(window);
    }

    shady_terminate();
    window_destroy(window);

    return EXIT_SUCCESS;
}
