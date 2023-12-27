#include "ui.hpp"

#include <iostream>

#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include <tinydir/tinydir.h>


void shady::UI::init() {
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true);
    ImGui_ImplOpenGL3_Init("#version 100");
}


void topbar_menu() {
    const char* BASE_DIR = "examples/"; 
    tinydir_dir dir;
    tinydir_open(&dir, BASE_DIR);

    if (ImGui::BeginMenu("Load")) {
        while (dir.has_next) {
            tinydir_file file;
            tinydir_readfile(&dir, &file);

            if (file.is_dir && file.name[0] != '.') {
                if (ImGui::MenuItem(file.name)) {
                    std::cout << "Opening Shaders: " << BASE_DIR << file.name << "/" << std::endl;
                }
            }

            tinydir_next(&dir);
        }
        ImGui::EndMenu();
    }

    tinydir_close(&dir);

    ImGui::Separator();

    if (ImGui::MenuItem("Quit")) {
        glfwSetWindowShouldClose(glfwGetCurrentContext(), GLFW_TRUE);
    }
}


void shady::UI::draw(bool& showMenu) {
    if (showMenu) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("Shaders")) {
                topbar_menu();
                ImGui::EndMenu();
            }

            ImGui::SameLine(ImGui::GetWindowWidth()-110);
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(150, 150, 150, 255));
            ImGui::Text("shady -- v%d.%d", shady::MAJOR_VERSION, shady::MINOR_VERSION);
            ImGui::PopStyleColor();

            ImGui::EndMainMenuBar();
        }

        ImGui::Render();
    }

    if (showMenu) {
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}


void shady::UI::terminate() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}