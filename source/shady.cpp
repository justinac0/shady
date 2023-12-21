#include "shady.hpp"

#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>


bool showMenu = true;
void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    if (key == GLFW_KEY_H && action == GLFW_PRESS) {
        showMenu = !showMenu;
    }

}


shady::Shady::Shady(int width, int height) {
    this->width = width;
    this->height = height;

    if (!glfwInit()) {
        // assert
    }

    this->pWindow = glfwCreateWindow(this->width, this->height, "shady", nullptr, nullptr);
    if (!this->pWindow) assert(this->pWindow != NULL);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwSetKeyCallback(this->pWindow, glfw_key_callback);

    glfwMakeContextCurrent(this->pWindow);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
}


shady::Shady::~Shady() {
    glfwTerminate();
}


inline void shady::Shady::handle_uniforms() {
    const GLuint programID = this->surface.get_program_id();

    int width, height;
    glfwGetWindowSize(this->pWindow, &width, &height);

    GLfloat dimensions[2] = {(GLfloat)width, (GLfloat)height};
    glUniform2fv(glGetUniformLocation(programID, "uResolution"), 1, dimensions);

    glUniform1f(glGetUniformLocation(programID, "uTime"), glfwGetTime());

    double xpos, ypos;
    glfwGetCursorPos(this->pWindow, &xpos, &ypos);

    GLfloat mousePosition[2] = {(GLfloat)xpos, (GLfloat)ypos};
    glUniform2fv(glGetUniformLocation(programID, "uMouse"), 1, mousePosition);
}

void shady::Shady::topbar_menu() {
    ImGui::MenuItem("(shady)", NULL, false, false);

    if (ImGui::BeginMenu("Load Shaders")) {
        ImGui::Text("Not Implemented!");
        ImGui::EndMenu();
    }

    ImGui::Separator();

    if (ImGui::Button("Quit")) {
        glfwSetWindowShouldClose(this->pWindow, GLFW_TRUE);
    }

}


void shady::Shady::run() {
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(this->pWindow, true);
    ImGui_ImplOpenGL3_Init("#version 100");

    while (!glfwWindowShouldClose(pWindow)) {
        glfwPollEvents();

        if (showMenu) {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            if (ImGui::BeginMainMenuBar()) {
                if (ImGui::BeginMenu("File")) {
                    this->topbar_menu();
                    ImGui::EndMenu();
                }

                ImGui::EndMainMenuBar();
            }

            ImGui::Render();
        }

        int display_w, display_h;
        glfwGetFramebufferSize(this->pWindow, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        this->surface.begin_draw();
        handle_uniforms();
        this->surface.end_draw();

        if (showMenu) {
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        glfwSwapBuffers(this->pWindow);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
