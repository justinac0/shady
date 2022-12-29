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
        shady_update();

        shady_draw();

        shady_ui_begin();
        shady_ui_char('A', 16, 16);
        shady_ui_char('b', 25, 16);
        shady_ui_char('c', 34, 16);
        shady_ui_char('!', 43, 16);
        shady_ui_end();

        shady_swapbuffers();
    }

    shady_ui_terminate();
    shady_terminate();

    return EXIT_SUCCESS;
}
