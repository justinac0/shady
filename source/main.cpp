#include "shady.hpp"
#include "debug.hpp"

int main(int argc, char const *argv[]) {
    shady::Shady shady(640, 480);
    shady.run();

    return EXIT_SUCCESS;
}
