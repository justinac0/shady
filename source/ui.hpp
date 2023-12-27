#pragma once

#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>


namespace shady {
    const int MAJOR_VERSION = 0; // temp
    const int MINOR_VERSION = 1;

    namespace UI {
        void init();
        void draw(bool& showMenu);
        void terminate();
    }

}