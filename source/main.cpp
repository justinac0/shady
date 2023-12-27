#include "shady.hpp"
#include "events/event_base.hpp"
#include "events/keyboard.hpp"
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>

void sleep(int64_t duration) {
    std::this_thread::sleep_for(std::chrono::seconds(5));
}

void testfn(std::mutex& mu, std::queue<shady::EventBase> eventQueue) {
    sleep(5);
    
    shady::KeyboardEvent quit(shady::EventType::QUIT, 0);
    
    mu.lock();
    eventQueue.push(quit);
    mu.unlock();
}

void render_thread(std::mutex& mu, std::queue<shady::EventBase> eventQueue) {
    shady::Shady shady(1280, 720);
    shady.surface.load("examples/default/vertex.glsl", "examples/default/fragment.glsl");
    shady.run();
}




// typedef enum {
//     QUIT,
//     RELOAD_SHADERS,
//     // PAUSE_TIME,
//     // FORWARD_TIME,
//     // BACKWARD_TIME,
//     IO_ERROR,
//     SHADER_ERROR,
//     LOAD_SHADERS,
//     // CREATE_PROJECT,
// } EventType;


// #define EVENT_SIZE 128
// typedef unsigned char Event[EVENT_SIZE];


// typedef struct EventHeader {
//     EventType type;
// } EventHeader;


// typedef struct KeyboardEvent {
//     EventHeader header;
// } KeyboardEvent;


// typedef struct IOEvent {
//     EventHeader header;
//     const char* message;
// } KeyboardEvent;


int main(int argc, char const *argv[]) {
    std::mutex mu;

    std::queue<shady::EventBase> eventQueue;

    std::thread rendering(&render_thread, std::ref(mu), std::ref(eventQueue));
    std::thread test(&testfn, std::ref(mu), std::ref(eventQueue));

    std::cout << "main, foo and bar now execute concurrently...\n";

    while (true) {
        mu.lock();
        while (!eventQueue.empty()) {
            shady::EventBase event = eventQueue.front();
            eventQueue.pop();

            switch (event.get_type()) {
                case shady::EventType::QUIT:
                    std::cout << "quit" << std::endl;
                    break;
                default:
                    break;
            }
        }

        mu.unlock();
    }

    rendering.join();
    test.join();
    
    return EXIT_SUCCESS;
}