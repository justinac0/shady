#include "shady.h"

#include <string.h>

/* ------ Graphics ---------------------------------------------------------- */

GLFWwindow* window = NULL;
ShadyInfo shadyInfo;


char* read_file(const char* path) {
    FILE* fileStream = fopen(path, "r");
    if (!fileStream) {
        printf("could not find file: %s\n", path);
        return NULL;
    }

    fseek(fileStream, SEEK_SET, SEEK_END);
    size_t size = ftell(fileStream);
    rewind(fileStream);
    char* buffer = (char*) malloc(size * sizeof(char) + 1);
    fread(buffer, sizeof(char), size, fileStream);
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

        GLchar* log = (GLchar*)calloc(length + 1, sizeof(GLchar));
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


GLint create_surface() {
    float quad[] = {
		-1, 1,
		 1, 1,
		 1,-1,
		-1,-1
	};

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(float), quad, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    return buffer;
}


/* -------------------------------------------------------------------------- */


static void glfw_key_callback(GLFWwindow* pWindow, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(pWindow, true);
    }
}


/* ------ Init -------------------------------------------------------------- */


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
    glfwSwapBuffers(window);
}


void shady_draw(void) {
    glUseProgram(shadyInfo.programID);

    glBindBuffer(GL_ARRAY_BUFFER, shadyInfo.surface);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_QUADS, 0, 4);

}


/* ------ Core -------------------------------------------------------------- */

void shady_uniform_defaults(void) {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    glUniform2fv(glGetUniformLocation(shadyInfo.programID, "u_ScreenResolution"), 1, (float[2]){width, height});

    double mx, my;
    glfwGetCursorPos(window, &mx, &my);
    glUniform2fv(glGetUniformLocation(shadyInfo.programID, "u_Mouse"), 1, (float[2]){mx, my});

    glUniform1f(glGetUniformLocation(shadyInfo.programID, "u_Time"), (float)glfwGetTime());
}

void shady_load(const char *vertexShader, const char *fragmentShader) {
    shadyInfo.vertexShader = create_shader(vertexShader, GL_VERTEX_SHADER);
    shadyInfo.fragmentShader = create_shader(fragmentShader, GL_FRAGMENT_SHADER);

    shadyInfo.programID = create_shader_program(shadyInfo.vertexShader, shadyInfo.fragmentShader);
    shadyInfo.surface = create_surface();
}


void shady_load_folder(const char *folder) {

}


void shady_load_default(void) {

}


/* ------ UI --------*/

void shady_ui_text(const char *text, int x, int y) {
    printf("%s\n", __func__);
}
