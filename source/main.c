#include <stdio.h>
#include <stdlib.h>


#define SHADY_INCLUDE_ALL
#include "shady.h"


int main(void) {
    shady_init(640, 480);
    shady_ui_init("EGA9x14.png");

    shady_load("examples/default/vertex.glsl", "examples/default/fragment.glsl");
    // shady_load("examples/rtw1/vertex.glsl", "examples/rtw1/fragment.glsl");

    while (shady_is_open()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0, 0, 0, 1);

        shady_update();

        shady_draw();

        // double xpos, ypos;
        // glfwGetCursorPos(glfwGetCurrentContext(), &xpos, &ypos);

        shady_ui_begin();
        shady_ui_char('A', 16, 16);
        shady_ui_char('b', 16 + 9, 16);
        shady_ui_char('c', 16 + 9 + 9, 16);
        shady_ui_end();

        glfwSwapBuffers(glfwGetCurrentContext());
    }

    shady_ui_terminate();
    shady_terminate();

    return EXIT_SUCCESS;
}
