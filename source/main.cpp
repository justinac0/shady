#include "shady.hpp"


int main(int argc, char const *argv[]) {
    shady::Shady shady(640, 480);
    shady.surface.load("examples/default/vertex.glsl", "examples/default/fragment.glsl");
    shady.run();

    return EXIT_SUCCESS;
}