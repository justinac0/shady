#include <stdio.h>
#include <stdlib.h>


#define SHADY_INCLUDE_ALL
#include "shady.h"


int main(void) {
    shady_init(640, 480);

    shady_load("examples/rtw1/vertex.glsl", "examples/rtw1/fragment.glsl");

    while (shady_is_open()) {
        shady_update();
        shady_uniform_defaults();
        shady_draw();
    }

    shady_terminate();

    return EXIT_SUCCESS;
}
