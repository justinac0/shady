#include "shady.hpp"

typedef enum {
    KEY_QUIT,
    KEY_REFRESH,
    KEY_HIDE_MENU,
    KEY_EVENT_COUNT
} KeyEventE;

std::queue<KeyEventE> keyQueue;

void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        keyQueue.push(KEY_QUIT);
    }

    if (key == GLFW_KEY_F5 && action == GLFW_PRESS) {
        keyQueue.push(KEY_REFRESH);    
    }

    if (key == GLFW_KEY_H && action == GLFW_PRESS) {
        keyQueue.push(KEY_HIDE_MENU);
    }
}


shady::Shady::Shady(int width, int height) {
    this->width = width;
    this->height = height;

    assert_stmt(!glfwInit());

    this->pWindow = glfwCreateWindow(this->width, this->height, "shady", nullptr, nullptr);
    assert_stmt(!this->pWindow);

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


void shady::Shady::run() {
    UI::init(this->pWindow);

    this->surface = shady::Surface::load_shader_dir_surface("examples/default");

    bool toggleMenu = true;
    while (!glfwWindowShouldClose(pWindow)) {
        glfwPollEvents();

        this->surface.begin_draw();

        int display_w, display_h;
        glfwGetFramebufferSize(this->pWindow, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        handle_uniforms();
        this->surface.end_draw();

        UI::draw(toggleMenu, surface);

        glfwSwapBuffers(this->pWindow);

        if (!keyQueue.empty()) {
            KeyEventE key_event = keyQueue.front();
            keyQueue.pop();
        
            switch (key_event) {
                default:
                    printf("Unknown Key Event...\n");
                    break;
                case KEY_QUIT:
                    printf("Quitting Shady...\n");
                    glfwSetWindowShouldClose(this->pWindow, GLFW_TRUE);
                    break;
                case KEY_HIDE_MENU:
                    printf("Toggling Menu...\n");
                    toggleMenu = !toggleMenu;
                    break;
                case KEY_REFRESH:
                    printf("Refreshing Shaders...\n");
                    this->surface = shady::Surface::load_shader_dir_surface(this->surface.shader_dir);
                    break;
            }
        }
    }

    UI::terminate();
}
