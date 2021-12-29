#include "s_internal.h"

GLuint s_internal_shader_create(const char* source, GLuint target) {
    GLuint shader;
    shader = glCreateShader(target);

	glShaderSource(shader, 1, (const char* const*)&source, 0);
	glCompileShader(shader);

	int compile_status = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
	if (compile_status == GL_FALSE) {
		unsigned int length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

		char* log = (char*) calloc(length, sizeof(char));

		glGetShaderInfoLog(shader, length, &length, &log[0]);
		glDeleteShader(shader);

        fprintf(stderr, "Compilation Error: %s.\n", log);
		free(log);

        return 0;
	}

	return shader;
}

extern void s_internal_shader_destroy(GLuint shader) {
    glDeleteShader(shader);
}

GLuint s_internal_program_create(GLuint vertex, GLuint fragment) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    glLinkProgram(program);

    int link_status = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &link_status);
    if (link_status == GL_FALSE) {
        unsigned int length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

        char* log = (char*) calloc(length, sizeof(char));
        glGetProgramInfoLog(program, length, &length, &log[0]);

        glDeleteProgram(program);

        s_internal_shader_destroy(vertex);
        s_internal_shader_destroy(fragment);

        fprintf(stderr, "Linking Error: %s\n", log);

        free(log);
    }

    return program;
}

extern void s_internal_program_destroy(GLuint program) {
    glDeleteProgram(program);
}

GLuint s_internal_surface_create(void) {
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
