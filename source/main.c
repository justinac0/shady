#include <stdio.h>
#include <stdlib.h>


#define SHADY_INCLUDE_ALL
#include "shady.h"


int main(void) {
    shady_init(640, 480);
    shady_ui_init("EGA9x14.png");

    shady_load("examples/default/vertex.glsl", "examples/default/fragment.glsl");

    while (shady_is_open()) {
        shady_update();

        shady_draw();
        shady_ui_char('c', 0, 0);

        glfwSwapBuffers(glfwGetCurrentContext());
    }

    shady_ui_terminate();
    shady_terminate();

    return EXIT_SUCCESS;
}
