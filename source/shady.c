#include "shady.h"

#include <string.h>

GLuint create_quad(int x, int y, float w, float h);

/* ------ Graphics ---------------------------------------------------------- */


char* read_file(const char* path) {
    FILE* fileStream = fopen(path, "r");
    if (!fileStream) {
        printf("could not find file: %s\n", path);
        return NULL;
    }

    fseek(fileStream, SEEK_SET, SEEK_END);
    size_t length = ftell(fileStream);
    rewind(fileStream);
    char* buffer = (char*) calloc(length + 1, sizeof(char));
    fread(buffer, sizeof(char), length, fileStream);
    return buffer;
}


GLuint create_shader(const char* shaderPath, GLenum type) {
    GLuint shader = glCreateShader(type);

    const char *source = read_file(shaderPath);
    const GLint length = strlen(source);

    glShaderSource(shader, 1, (const char* const*)&source, &length);
    glCompileShader(shader);

    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (success == 0) {
        GLint length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

        GLchar* log = (GLchar*)calloc(length + 1, sizeof(GLchar));
        glGetShaderInfoLog(shader, length, &length, &log[0]);

        printf("[shader::%s] -- %s\n", shaderPath, log);
        free(log);

        glDeleteShader(shader);
    }

    return shader;
}

GLuint create_shader_from_source(const char* source, GLenum type) {
    GLuint shader = glCreateShader(type);
    const GLint length = strlen(source);

    glShaderSource(shader, 1, (const char* const*)&source, &length);
    glCompileShader(shader);

    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (success == 0) {
        GLint length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

        GLchar* log = (GLchar*)calloc(length + 1, sizeof(GLchar));
        glGetShaderInfoLog(shader, length, &length, &log[0]);

        printf("[shader] -- %s\n", log);
        free(log);

        glDeleteShader(shader);
    }

    return shader;
}



GLuint create_shader_program(GLuint vertexShader, GLuint fragmentShader) {
    GLuint programID = glCreateProgram();

    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);

    glLinkProgram(programID);

    GLint linked = 0;
    glGetProgramiv(programID, GL_LINK_STATUS, (int*)&linked);

    if (linked == 0) {
        GLint length = 0;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &length);

        GLchar* log = (GLchar*) calloc(length + 1, sizeof(GLchar));
        glGetProgramInfoLog(programID, length, &length, &log[0]);

        printf("[shader_program] -- %s\n", log);
        free(log);

        glDeleteProgram(programID);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    glDetachShader(programID, vertexShader);
    glDetachShader(programID, fragmentShader);

    return programID;
}


GLuint create_quad(int x, int y, float w, float h) {

    float ww = w/640.f;
    float hh = h/480.f;

    float xoffs = 2*x/640.f + ww;
    float yoffs = 2*y/480.f + hh;

    float quad[] = {
		(-ww) - (1 - xoffs), ( hh) + (1 - yoffs), // tl
		( ww) - (1 - xoffs), ( hh) + (1 - yoffs), // tr
		( ww) - (1 - xoffs), (-hh) + (1 - yoffs), // br
		(-ww) - (1 - xoffs), (-hh) + (1 - yoffs)  // bl
	};

    int ints[] = {
        0, 1, 2,
        0, 2, 3
    };

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint ido;
	glGenBuffers(1, &ido);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ido);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ints), ints, GL_STATIC_DRAW);

    GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    return vao;
}


/* -------------------------------------------------------------------------- */

bool polys = true; // temp

static void glfw_key_callback(GLFWwindow* pWindow, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(pWindow, true);
    }

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        polys = !polys;
    }
}


/* ------ Init -------------------------------------------------------------- */


GLFWwindow* window = NULL;
ShadyInfo shadyInfo;


bool shady_init(int width, int height) {
    if (!glfwInit()) {
        return false;
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(width, height, "shady", NULL, NULL);
    if (!window) {
        return false;
    }

    glfwSetKeyCallback(window, glfw_key_callback);

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    glfwSwapInterval(1);

    return true;
}


void shady_terminate(void) {
    glfwDestroyWindow(window);
    glfwTerminate();
}


bool shady_is_open(void) {
    return !glfwWindowShouldClose(window);
}


void shady_update(void) {
    glfwPollEvents();
    polys ? glPolygonMode(GL_FRONT_AND_BACK, GL_FILL) : glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}


void shady_draw(void) {
    glUseProgram(shadyInfo.programID);

    // TODO: move uniform retrival to callbacks
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    glUniform2fv(glGetUniformLocation(shadyInfo.programID, "uResolution"), 1, (float[2]){width, height});

    glUniform1f(glGetUniformLocation(shadyInfo.programID, "uTime"), glfwGetTime());

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    glUniform2fv(glGetUniformLocation(shadyInfo.programID, "uMouse"), 1, (float[2]){xpos, ypos});


    glBindVertexArray(shadyInfo.surface);
    glEnableVertexAttribArray(0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glUseProgram(0);
}


/* ------ Core -------------------------------------------------------------- */

void shady_load(const char *vertexShader, const char *fragmentShader) {
    shadyInfo.vertexShader = create_shader(vertexShader, GL_VERTEX_SHADER);
    shadyInfo.fragmentShader = create_shader(fragmentShader, GL_FRAGMENT_SHADER);

    shadyInfo.programID = create_shader_program(shadyInfo.vertexShader, shadyInfo.fragmentShader);
    shadyInfo.surface = create_quad(0, 0, 640, 480); // get width and height from callbacks...
}


void shady_load_folder(const char *folder) {

}


void shady_load_default(void) {

}


/* ------ UI --------*/
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

const char* UI_VERT_SHADER ="#version 400\n"\
"layout (location = 0) in vec2 positions;\n"\
"layout (location = 1) in vec2 in_texture;\n"\
"out vec2 out_texture;\n"\
"void main() {\n"\
"gl_Position = vec4(positions, 0, 1);\n"\
"out_texture = in_texture;\n"\
"}";

const char* UI_FRAG_SHADER ="#version 400\n"\
"in vec2 out_texture;\n"\
"uniform sampler2D our_texture;\n"\
"void main() {\n"\
"vec3 col = vec3(1);\n"\
"gl_FragColor = texture(our_texture, out_texture);\n"\
"}";

typedef struct ShadyUI {
    int width;
    int height;
    GLuint fontID;
    GLuint programID;
} ShadyUI;

ShadyUI uiInfo;

void shady_ui_init(const char* fontPath) {
    // setup ui shaders   
    GLuint vertexShader = create_shader_from_source(UI_VERT_SHADER, GL_VERTEX_SHADER);
    GLuint fragmentShader = create_shader_from_source(UI_FRAG_SHADER, GL_FRAGMENT_SHADER);

    uiInfo.programID = create_shader_program(vertexShader, fragmentShader);

    // load texture
    glGenTextures(1, &uiInfo.fontID);
    glBindTexture(GL_TEXTURE_2D, uiInfo.fontID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int w, h, comp;
    unsigned char* image = stbi_load(fontPath, &w, &h, &comp, STBI_rgb);
    if (image) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(image);
    }

    printf("loaded_texture: %s, %dx%d\n", fontPath, w, h);
}


void shady_ui_terminate(void) {
    
}


void shady_ui_begin() {

}


void shady_ui_end() {

}


void shady_ui_char(const char c, int x, int y) {
    int col = c % 16;
    int row = c / 16; 

    GLuint quad = create_quad(x, y, 9, 14);
    glBindVertexArray(quad);

    float textureCoords[] = {
        col*(1.f/16.f), row*(1.f/16.f),
        (1.f + col)*(1.f/16.f), row*(1.f/16.f),
        (1.f + col)*(1.f/16.f), (1.f + row)*(1.f/16.f),
        col*(1.f/16.f), (1.f + row)*(1.f/16.f),
    };

    GLuint tbo;
	glGenBuffers(1, &tbo);
	glBindBuffer(GL_ARRAY_BUFFER, tbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords), textureCoords, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);

    glUseProgram(uiInfo.programID);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


void shady_ui_text(const char *text, int x, int y) {

}
