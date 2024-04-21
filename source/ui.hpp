#pragma once

#include <iostream>
#include <vector>

#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include <tinydir/tinydir.h>

#include "surface.hpp"

namespace shady {
    const int MAJOR_VERSION = 0; // temp
    const int MINOR_VERSION = 1;

    namespace UI {
        void init(void* window);
        void draw(bool& showMenu, shady::Surface &dir_load_cb);
        void terminate();
    }

}
