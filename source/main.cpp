#include "shady.hpp"
#include "debug.hpp"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int main(int argc, char const *argv[]) {
    shady::Shady shady(WINDOW_WIDTH, WINDOW_HEIGHT);
    shady.run();

    return EXIT_SUCCESS;
}
