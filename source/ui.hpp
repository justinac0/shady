#pragma once

#include <GLFW/glfw3.h>


namespace shady {
    const int MAJOR_VERSION = 0;
    const int MINOR_VERSION = 1;

    class UI {
        public:
            static void init();
            static void draw(bool& showMenu);
            static void terminate();
        private:
    };

}