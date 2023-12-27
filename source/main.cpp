#include "shady.hpp"
#include <iostream>
#include <thread>
#include <mutex>

void foo(std::mutex mu, size_t* counter) {
    shady::Shady shady(1280, 720);
    shady.surface.load("examples/default/vertex.glsl", "examples/default/fragment.glsl");
    shady.run();
}


void bar(std::mutex mu, const size_t* counter) {
    while (true) {
        std::cout << "Worker thread: " << *counter << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}


int main(int argc, char const *argv[]) {
    std::mutex mu;

    size_t counter = 0;
    std::thread primary(&foo, &counter);
    std::thread worker(&bar, &counter);

    std::cout << "main, foo and bar now execute concurrently...\n";

    primary.join();
    worker.join();

    return EXIT_SUCCESS;
}