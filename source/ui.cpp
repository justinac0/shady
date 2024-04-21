#include "ui.hpp"


// IMPORTANT: my name is c++ i parse a file in 1 go (single-pase compiler be like, doo-didodo - Zyrn)...
std::vector<tinydir_file> get_directory_contents(const char* directory);
bool is_valid_shader_dir(tinydir_file file);
std::vector<std::string> get_dirs(const char* baseDir);


void shady::UI::init(void* window) {
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)window, true);
    ImGui_ImplOpenGL3_Init("#version 100");
}


bool is_valid_shader_dir(tinydir_file file) {
    const char* VERTEX_NAME = "vertex.glsl";
    const char* FRAGMENT_NAME = "fragment.glsl";
    // const std::string COMPUTE_NAME = "compute.glsl";

    const std::string filename = std::string(file.name);

    const bool isDirectory = file.is_dir;
    const bool isHidden = filename.find(".", 0) == 0;

    bool hasVertexShader = false;
    bool hasFragmentShader = false;

    auto dir_contents = get_directory_contents(file.path);
    for (auto file : dir_contents) {
        if (!file.is_reg) {
            continue;
        }

        std::string fname(file.name);

        if (fname.compare(VERTEX_NAME)) {
            hasVertexShader = true;
        }
        if (fname.compare(FRAGMENT_NAME)) {
            hasFragmentShader = true;
        }
    }

    return isDirectory && !isHidden &&
        hasVertexShader && hasFragmentShader;
}


std::vector<std::string> get_dirs(const char* baseDir) {
    std::vector<std::string> dirs;
    
    std::vector<tinydir_file> contents = get_directory_contents(baseDir);
    for (auto file : contents) {
        if (is_valid_shader_dir(file)) {
            dirs.push_back(std::string(file.path) + "/");
        }
    }

    return dirs;
}


std::vector<tinydir_file> get_directory_contents(const char* directory) {
    std::vector<tinydir_file> files;

    tinydir_dir dir;
    if (tinydir_open(&dir, directory) == -1) {
        return files;
    }

    while (dir.has_next) {
        tinydir_file file;
        
        if (tinydir_readfile(&dir, &file) != -1) {
            files.push_back(file);
        }

        tinydir_next(&dir);
    }

    tinydir_close(&dir);

    return files;
}


void topmenu(std::vector<std::string> dirs, shady::Surface &surface) {
    if (ImGui::BeginMenu("Load")) {
        
        for (auto path : dirs) {
            if (ImGui::MenuItem(path.c_str())) {
                std::cout << "Opening Shaders: " << path << std::endl; // send to event handler
                surface = shady::Surface::load_shader_dir_surface(path);
            }
        }
  
        ImGui::EndMenu();
    }

    ImGui::Separator();

    if (ImGui::MenuItem("Quit")) {
        exit(0); // surely unsafe :)
    }
}


void shady::UI::draw(bool& showMenu, shady::Surface &surface) {
    if (showMenu) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("Shaders")) {
                topmenu(get_dirs("./examples"), surface); // fixme: stop running on every frame, instead watch folders / files for hotloading
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
